#
# BitBang (http://www.bitbang.org)
# Copyright (C) 2004-2009 Tiago Baptista
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

INCLUDE (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

# Main source files
SET (BBSE_SRCS CDefaultEventHandler.cpp CEventHandler.cpp CPhysicsObject.cpp CSimObject.cpp CWorld.cpp CFileConfig.cpp CObjectLabel.cpp CTimedLabel.cpp CIrrMotionState.cpp)

INCLUDE_DIRECTORIES (. ../bitbang ../irrlicht/include ../bullet/include simpleopt)

IF (WIN32)
	SET (IRRLICHT_LINK ../irrlicht/lib/Win32-gcc)
ENDIF (WIN32)
IF (UNIX)
	IF (APPLE)
		SET (IRRLICHT_LINK ../irrlicht/lib/MacOSX)
		SET (BULLET_LINK ../bullet/lib/MacOSX)
		SET (OPENGL_LIBRARIES ${OPENGL_LIBRARIES} "-framework Cocoa -framework Carbon -framework IOKit")
	ELSE (APPLE)
		SET (IRRLICHT_LINK ../irrlicht/lib/Linux ../irrlicht/lib/Linux64)
		SET (BULLET_LINK ../bullet/lib/Linux ../bullet/lib/Linux64)
	ENDIF (APPLE)
ENDIF (UNIX)

LINK_DIRECTORIES (${IRRLICHT_LINK} ${BULLET_LINK})

ADD_LIBRARY (BitBangSE STATIC ${BBSE_SRCS})

ADD_DEPENDENCIES (BitBangSE BitBang)

TARGET_LINK_LIBRARIES (BitBangSE BitBang Irrlicht BulletDynamics BulletCollision LinearMath ${OPENGL_LIBRARIES})
