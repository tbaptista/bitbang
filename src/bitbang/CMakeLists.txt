#
# BitBang (http://www.bitbang.org)
# Copyright (C) 2004-2017 Tiago Baptista
#						  Telmo Menezes
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


SET (BITBANG_SRCS BBAction.cpp BBBrain.cpp BBFeature.cpp BBObject.cpp BBPerception.cpp BBPerceptionSphere.cpp BBRule.cpp BBRuleCondition.cpp BBRuleList.cpp BBRandomRuleList.cpp BBRuleListEditype.cpp BBRuleListEditor.cpp BBSchedule.cpp BBTimer.cpp BBVisionReach3DCone.cpp BBVisionReach2DCircle.cpp BBWorld.cpp BBCSVFileLog.cpp  BBFileLog.cpp BBLog.cpp features/BBFeatureBoolean.cpp features/BBFeatureNumber.cpp features/BBFeatureString.cpp perceptions/BBPerceptionBoolean.cpp perceptions/BBPerceptionFeatureNumber.cpp perceptions/BBPerceptionFixedNumber.cpp perceptions/BBPerceptionNumber.cpp perceptions/BBPerceptionString.cpp perceptions/BBPerceptionFixedString.cpp perceptions/BBPerceptionFeatureString.cpp perceptions/BBPerceptionFeatureBoolean.cpp perceptions/BBPerceptionRandom.cpp perceptions/BBPerceptionRandomNumber.cpp perceptions/BBPerceptionRandomProbability.cpp perceptions/BBPerceptionReachResource.cpp perceptions/BBPerceptionSeeResource.cpp schedules/BBLogSchedule.cpp BBRandomGenerator.cpp ${BITBANG_SOURCE_DIR}/sfmt/SFMT.c)

SET (BITBANG_INSTALL_LIBDIR lib)

IF (WIN32)
	SET (BITBANG_SRCS ${BITBANG_SRCS} BBOSWin32.cpp)
	SET (BITBANG_INSTALL_LIBDIR lib/Win32)
ENDIF (WIN32)
IF (UNIX)
	IF (APPLE)
		SET (BITBANG_SRCS ${BITBANG_SRCS} BBOSMacOSX.cpp)
		SET (BITBANG_INSTALL_LIBDIR lib/MaxOSX)
	ELSE (APPLE)
		SET (BITBANG_SRCS ${BITBANG_SRCS} BBOSLinux.cpp)
		IF (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
			SET (BITBANG_INSTALL_LIBDIR lib/Linux64)
		ELSEIF (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
			SET (BITBANG_INSTALL_LIBDIR lib/Linux)
		ENDIF ()
	ENDIF (APPLE)
ENDIF (UNIX)

add_definitions(-DSFMT_MEXP=19937)
add_definitions(-DHAVE_SSE2)
add_definitions(-msse2)

include_directories (. features perceptions ${BITBANG_SOURCE_DIR}/sfmt)

add_library (BitBang STATIC ${BITBANG_SRCS})

install (TARGETS BitBang ARCHIVE DESTINATION "bitbang/${BITBANG_INSTALL_LIBDIR}")
install (DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/" DESTINATION "bitbang/include" FILES_MATCHING PATTERN "*.h")
