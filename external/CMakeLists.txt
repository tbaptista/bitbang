#
# BitBang (http://www.bitbang.org)
# Copyright (C) 2017 Tiago Baptista
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the version 2 of the GNU General Public License
# as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

cmake_minimum_required(VERSION 2.8.11)

project(BitBangDependencies)

include(ExternalProject)

# Bullet Libraries
set (bullet_CMAKE_ARGS
	-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
	-DBUILD_SHARED_LIBS=OFF 
	-DBUILD_EXTRAS=OFF 
	-DBUILD_PYBULLET=OFF 
	-DBUILD_BULLET3=OFF 
	-DBUILD_BULLET2_DEMOS=OFF
	-DBUILD_OPENGL3_DEMOS=OFF
	-DBUILD_CPU_DEMOS=OFF
	-DBUILD_UNIT_TESTS=OFF
)

ExternalProject_Add(bullet
	URL				https://github.com/bulletphysics/bullet3/archive/2.86.1.tar.gz
	URL_MD5			439f78f567ee340b0cd1ffb8c31def1e
	INSTALL_DIR		${CMAKE_SOURCE_DIR}/external/bullet
	CMAKE_ARGS		${bullet_CMAKE_ARGS}
)

# Irrlicht Libraries
if(APPLE)
	set(IRRLICHT_BUILD_CMD cd <SOURCE_DIR>/source/Irrlicht/MacOSX && xcodebuild -project MacOSX.xcodeproj -target libIrrlicht.a)
	set(IRRLICHT_INSTALL_CMD mkdir -p <INSTALL_DIR>/lib && cp <SOURCE_DIR>/source/Irrlicht/MacOSX/build/Release/libIrrlicht.a <INSTALL_DIR>/lib && cp -r <SOURCE_DIR>/include <INSTALL_DIR>/)
else()
	set(IRRLICHT_BUILD_CMD cd <SOURCE_DIR>/source/Irrlicht && make NDEBUG=1)
	set(IRRLICHT_INSTALL_CMD mkdir -p <INSTALL_DIR>/lib && cp libIrrlicht.a <INSTALL_DIR>/lib && cp -r <SOURCE_DIR>/include <INSTALL_DIR>/)
endif()

ExternalProject_Add(irrlicht
	URL				https://downloads.sourceforge.net/irrlicht/irrlicht-1.8.4.zip
	URL_MD5			9401cfff801395010b0912211f3cbb4f
	BUILD_IN_SOURCE	1
	CONFIGURE_COMMAND ""
	PATCH_COMMAND	patch source/Irrlicht/MacOSX/CIrrDeviceMacOSX.mm ${CMAKE_SOURCE_DIR}/external/irrlicht-1.8.4.patch
	BUILD_COMMAND	${IRRLICHT_BUILD_CMD}
	INSTALL_COMMAND ${IRRLICHT_INSTALL_CMD}
	INSTALL_DIR		${CMAKE_SOURCE_DIR}/external/irrlicht
)
