# OpenWrt fork with added support for building under cygwin

This is the fork of the OpenWrt patched to be buildable under cygwin.

### Prerequisites

* Recent version of cygwin (tested with 3.0 x64 on Windows 10)
* Case sensitive folder or filesystem to clone OpenWrt to.
  Setup detailed [here](https://cygwin.com/cygwin-ug-net/using-specialnames.html#pathnames-casesensitive)
* "cygwin" type symbolic links - might hit problems with linux kernel compilation otherwise.
  It meand that there should be no "winsymlinks" in CYGWIN environment variable.
  Details available [here](https://cygwin.com/cygwin-ug-net/using-cygwinenv.html).
* Relevant cygwin development packages installed: make, gcc and g++ 4.8+, libncurses-devel,
  perl, perl(Thread::Queue), tar, findutils, patch, diffutils, fileutils, gawk, grep, unzip,
  bzip2, wget, python, git.
* In case your image includes u-boot you will also nees these deps: xxd, swig, python2-devel.
* Compiled and installed [upoll](https://github.com/lexa2/upoll) and [cygepoll](https://github.com/lexa2/cygepoll).
  (autoconf and automake cygwin packages are required to complete this step)
* Do not use "noacl" for the mountpoint openwrt is cloned to. It will result in rootfs permissions screwed up
  and built image falling with kernel panic as soon as it tries to execute init.
* A lot of patience as compiling openwrt under cygwin is way slower compared to normal linux build.
* Good idea would be to add cygwin and openwrt clone folder into the exceptions list of your antivirus.
  Adding relevant folders into exceptions of built-in Windows 10 defender resulted in 3x reduced compile time.

### Installing

Follow the usual openwrt building procedure - just the same way it is done on linux:
```
# git clone https://github.com/lexa2/openwrt.git
# cd openwrt
# git checkout --track origin/openwrt-18.06-cygwin
# { echo CONFIG_TARGET_mediatek=y; echo CONFIG_TARGET_mediatek_mt7623=y; echo CONFIG_TARGET_mediatek_mt7623_DEVICE_7623n-bananapi-bpi-r2=y; } > .config
# { echo CONFIG_DEVEL=y; echo CONFIG_CCACHE=y; } >> .config
# make defconfig
# make -j16
```

### Known issues

* Most of the packages that are included in the OpenWrt are to be only cross-compiled for the target system and have
  nothing to with the host OS and its environment. OpenWrt is a really clever system that self-builds the entire
  toolchain for cross-compiling. Thus there should be no problems with compiling most packages under cygwin as long 
  as OpenWrt managed to compile its toolchain. But there's a minority of packages that are built (at least partly) 
  with host system as a target. Good example is the {ncurses package](https://github.com/lexa2/openwrt/blob/v18.06.2/package/libs/ncurses/Makefile) 
  which build tic tool on the host and use it to generate terminfo definitions to be included into resulting package. 
  
  Packages of this kind may and will cause all kind of pains when building under cygwin. One of the frequently used 
  package you're most probably will encounter is the u-boot. There are several problems with it that one will have to 
  handle:
  1. In most versions of u-boot Makefile includes enforcement of the ANSI C mode when host OS is cygwin. 
     This is wrong. And it results in u-boot compilation failure from the very start.
	 It should be patched out like it was done in [here](https://github.com/lexa2/openwrt/blob/0145afd394214b1562382518a3f3970c5ecd3628/package/boot/uboot-mediatek/patches/0900-fix-hostcflags-under-cygwin.patch).
  2. U-boot heavily relies on linux-specific macros and types like __be32 or __swig32. Under cygwin the only
     option is to feed u-boot with what it wants by providing a sufficient mimimal subset of relevant headers.
	 Good example on how to do it is available [here](https://github.com/lexa2/openwrt/commit/0145afd394214b1562382518a3f3970c5ecd3628#diff-3897d3a104290123d4d1b617665f498c).
	 Please be sure to open up a pull request against this repo with board specific changes to related u-boot package.
	 Thanks for contributing.
* Sometimes strange and hard to understand issues arise related to the permissions of the files that are copied or 
  created during the build. Typically the problem manifest itself as a build failure with error messages stating
  "permission denided". Actual problem is that windows ACL on the files/folders where you build OpenWRT got changed
  from what they were set to initially by the cygwin. Most of the time the problem is caused by someone opening up
  the permissions tab on folder properties and allowing windows explorer to "fix the order of the ACL rules".  
  
  To reset permissions into sensible defaults one may try to start up mintty as Administrator and execute the following:
  ```
  $ cd /path/to/openwrt
  $ setfacl -k -b .
  $ chown $(id -un) .
  $ chmod ug+rwx .
  $ find . -type f -exec setfacl -k -b \{\} \;
  $ find . -type f -exec chown $(id -un) \{\} \;
  $ find . -type f -exec chmod ug+rw \{\} \;
  $ find . -type d -exec setfacl -k -b \{\} \;
  $ find . -type d -exec chown $(id -un) \{\} \;
  $ find . -type d -exec chmod ug+rwx \{\} \;
  ```

## Authors

* **Alexey Loukianov** - *Initial work on cygwin compatibility for OpenWrt*

See also the list of authors and contributors who participated in [this](https://github.com/lexa2/openwrt/contributors) and [upstream](https://github.com/openwrt/openwrt/contributors) projects.

## License

This project is licensed under the same license as upstream project - i.e. OpenWrt.
Check [upstream](https://github.com/openwrt/openwrt) for more details.
