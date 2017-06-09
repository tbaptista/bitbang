#
# BitBang (http://www.bitbang.org)
# Copyright (C) 2004-2017 Tiago Baptista
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
SET (BBSE_SRCS CDefaultEventHandler.cpp CEventHandler.cpp CEventReceiver.cpp  CPhysicsObject.cpp CSimObject.cpp CWorld.cpp CFileConfig.cpp CObjectLabel.cpp CTimedLabel.cpp CIrrMotionState.cpp)
SET (BBSE_INSTALL_LIBDIR lib)

INCLUDE_DIRECTORIES (. ${BITBANG_SOURCE_DIR}/bitbang ${BITBANG_SOURCE_DIR}/irrlicht/include ${BITBANG_SOURCE_DIR}/bullet/include simpleopt)

IF (WIN32)
	SET (IRRLICHT_LINK ${BITBANG_SOURCE_DIR}/irrlicht/lib/Win32-gcc)
	SET (BBSE_INSTALL_LIBDIR lib/Win32)
ENDIF (WIN32)
IF (UNIX)
	IF (APPLE)
		SET (IRRLICHT_LINK ${BITBANG_SOURCE_DIR}/irrlicht/lib/MacOSX)
		SET (BULLET_LINK ${BITBANG_SOURCE_DIR}/bullet/lib/MacOSX)
		SET (OPENGL_LIBRARIES ${OPENGL_LIBRARIES} "-framework Cocoa -framework Carbon -framework IOKit")
		SET (BBSE_INSTALL_LIBDIR lib/MaxOSX)
	ELSE (APPLE)
		SET (IRRLICHT_LINK ${BITBANG_SOURCE_DIR}/irrlicht/lib/Linux ${BITBANG_SOURCE_DIR}/irrlicht/lib/Linux64)
		SET (BULLET_LINK ${BITBANG_SOURCE_DIR}/bullet/lib/Linux ${BITBANG_SOURCE_DIR}/bullet/lib/Linux64)
		IF (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
			SET (BBSE_INSTALL_LIBDIR lib/Linux64)
		ELSEIF (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
			SET (BBSE_INSTALL_LIBDIR lib/Linux)
		ENDIF ()
	ENDIF (APPLE)
ENDIF (UNIX)

LINK_DIRECTORIES (${IRRLICHT_LINK} ${BULLET_LINK})

ADD_LIBRARY (BitBangSE STATIC ${BBSE_SRCS})

ADD_DEPENDENCIES (BitBangSE BitBang)

TARGET_LINK_LIBRARIES (BitBangSE BitBang Irrlicht BulletDynamics BulletCollision LinearMath ${OPENGL_LIBRARIES})

install (TARGETS BitBangSE ARCHIVE DESTINATION "bitbang/${BBSE_INSTALL_LIBDIR}")
install (DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/" DESTINATION "bitbang/include" FILES_MATCHING PATTERN "*.h")
