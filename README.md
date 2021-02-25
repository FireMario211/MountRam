# MountRam

A Linux Utility that allows you to easily mount your ram (Ram Disk)

By FireMario211

Version 1.0.0

## How to install MountRam
* Required Packages to build
	* `build-essentials`
	* `gcc`
	* `make`

* Installation
```
git clone https://github.com/FireMario211/MountRam.git
cd MountRam
./configure
make
make install (May require root access)
```

## How to use
* `--help`, `-h`
	* Lists all available commands
* `--version`, `-v`
	* Shows the version (1.0.0)
* `--setup`, `-s`
	* Prompts you with questions and mounts ram
* `--mount <Name> <Size> <Path>`, `-M`
	* Manually sets up mounting the ram
* `--umount <Path>`, `-u`
	* Unmounts the Ram Directory (Must be mounted first)

## How to mount Ram Disk
It's very simple to mount a Ram Disk using MountRam, there are 2 options you can use, `--mount` or `--setup`

### Setup Method
First you will need to run `mountram --setup` to run the setup, and it will prompt you questions, below will be an example of what to enter:
```
Please insert the mount name (No spaces): rammount

Please insert the path (Ex: /mnt/ram): /mnt

Please enter in the size (Ex: 1G): 4G
Successfully mounted!
```
Then after that, it should set up the ram disk!

### Manual Method
If you want to mount the Ram Disk quick, you can use `mountram --mount`, though you will need to specify the name, size, and path.

An example of using the command would be: `mountram --mount rammount 4G /mnt`, which will be similar to setup, without the prompts.

### Unmounting the Ram Disk (Root access may be required)
If you want to unmount the Ram Disk, there are 3 ways you can unmount it.
1. Using `mountram --umount`
2. Using `umount`
3. Rebooting system

For using `mountram --umount`, it's pretty simple, all you will have to do is just specify the path of where you mounted after, so for instance, if I mounted at `/mnt`, I would type `mountram --umount /mnt`.

For using `umount`, I probably won't go into detail of how to use it, as it's similar to using `mountram --umount`, all you will really have to do is `umount /mnt`, assuming you mounted from `/mnt`.


------------

This project was only just an attempt to make a package, there are probably other alternatives to this, or you can simply just use `mount`.