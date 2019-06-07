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
* Compiled and installed [upoll](https://github.com/lexa2/upoll) and [cygepoll](https://github.com/lexa2/cygepoll).
  (autoconf and automake cygwin packages are required to complete this step)
* Safe bet would be to use "noacl" for the mountpoint openwrt is cloned to. There might be weird permission-related
  issues otherwise like files having 040 mode and being unreadable after openwrt applying a patch.
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

## Authors

* **Alexey Loukianov** - *Initial work on cygwin compatibility for OpenWrt*

See also the list of authors and contributors who participated in [this](https://github.com/lexa2/openwrt/contributors) and [upstream](https://github.com/openwrt/openwrt/contributors) projects.

## License

This project is licensed under the same license as upstream project - i.e. OpenWrt.
Check [upstream](https://github.com/openwrt/openwrt) for more details.
