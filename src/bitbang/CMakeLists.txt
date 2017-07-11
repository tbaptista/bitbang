#
# BitBang (http://www.bitbang.org)
# Copyright (C) 2004-2008 Tiago Baptista
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


SET (BITBANG_SRCS schedules/BBScheduleScriptable.cpp BBInfluence.cpp BBInfluenceMap.cpp BBAction.cpp BBBrain.cpp BBFeature.cpp BBObject.cpp BBPerception.cpp BBPerceptionSphere.cpp BBRule.cpp BBRuleCondition.cpp BBRuleList.cpp BBRandomRuleList.cpp BBRuleListEditype.cpp BBRuleListEditor.cpp BBSchedule.cpp BBTimer.cpp BBVisionReach3DCone.cpp BBVisionReach2DCircle.cpp BBWorld.cpp BBCSVFileLog.cpp BBFileLog.cpp BBLog.cpp features/BBFeatureBoolean.cpp features/BBFeatureNumber.cpp features/BBFeatureString.cpp perceptions/BBPerceptionBoolean.cpp perceptions/BBPerceptionFeatureNumber.cpp perceptions/BBPerceptionFixedNumber.cpp perceptions/BBPerceptionNumber.cpp perceptions/BBPerceptionString.cpp perceptions/BBPerceptionFixedString.cpp perceptions/BBPerceptionFeatureString.cpp perceptions/BBPerceptionFeatureBoolean.cpp perceptions/BBPerceptionRandom.cpp perceptions/BBPerceptionRandomNumber.cpp perceptions/BBPerceptionRandomProbability.cpp perceptions/BBPerceptionReachResource.cpp perceptions/BBPerceptionSeeResource.cpp perceptions/BBPerceiveLocation.cpp schedules/BBLogSchedule.cpp BBRandomGenerator.cpp ../sfmt/SFMT.c GridLayer/GridLattice.cpp GridLayer/GridMapLayer.h)

SET(CMAKE_BUILD_TYPE Debug)

IF (WIN32)
	SET (BITBANG_SRCS ${BITBANG_SRCS} BBOSWin32.cpp)
ENDIF (WIN32)
IF (UNIX)
	IF (APPLE)
		SET (BITBANG_SRCS ${BITBANG_SRCS} BBOSMacOSX.cpp)
	ELSE (APPLE)
		SET (BITBANG_SRCS ${BITBANG_SRCS} BBOSLinux.cpp)
	ENDIF (APPLE)
ENDIF (UNIX)

add_definitions(-DMEXP=19937)
add_definitions(-DHAVE_SSE2)
add_definitions(-msse2)

include_directories (. features perceptions ../sfmt)

add_library (BitBang STATIC ${BITBANG_SRCS})
