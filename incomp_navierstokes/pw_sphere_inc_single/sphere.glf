#
# radius of sphere is fixed at sqrt(3)
#

package require PWI_Glyph 2

set sr2 [expr sqrt(3)/sqrt(2)]
set sr3 [expr sqrt(3)]

#puts "value of sr2= $sr2 and sr3= $sr3"

proc makeSphere { nds dr far } {

set _DB(1) [pw::Point create]
$_DB(1) setPoint {1.2247 1.2247 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(2) [pw::Point create]
$_DB(2) setPoint {1.2247 -1.2247 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(3) [pw::Point create]
$_DB(3) setPoint {-1.2247 1.2247 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(4) [pw::Point create]
$_DB(4) setPoint {-1.2247 -1.2247 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(5) [pw::Point create]
$_DB(5) setPoint {0 1.2247 1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(6) [pw::Point create]
$_DB(6) setPoint {0 1.2247 -1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}
 
set _DB(7) [pw::Point create]
$_DB(7) setPoint {0 -1.2247 1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(8) [pw::Point create]
$_DB(8) setPoint {0 -1.2247 -1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(9) [pw::Point create]
$_DB(9) setPoint {1.2247 0 1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}
 
set _DB(10) [pw::Point create]
$_DB(10) setPoint {1.2247 0 -1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(11) [pw::Point create]
$_DB(11) setPoint {-1.2247 0 1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(12) [pw::Point create]
$_DB(12) setPoint {-1.2247 0 -1.2247}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(13) [pw::Point create]
$_DB(13) setPoint {1.732 0 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(14) [pw::Point create]
$_DB(14) setPoint {-1.732 0 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(15) [pw::Point create]
$_DB(15) setPoint {0 1.732 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(16) [pw::Point create]
$_DB(16) setPoint {0 -1.732 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(17) [pw::Point create]
$_DB(17) setPoint {0 0 1.732}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(18) [pw::Point create]
$_DB(18) setPoint {0 0 -1.732}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(19) [pw::Point create]
$_DB(19) setPoint {1 1 1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(20) [pw::Point create]
$_DB(20) setPoint {-1 1 1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(21) [pw::Point create]
$_DB(21) setPoint {-1 -1 1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(22) [pw::Point create]
$_DB(22) setPoint {1 -1 1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(23) [pw::Point create]
$_DB(23) setPoint {1 1 -1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(24) [pw::Point create]
$_DB(24) setPoint {-1 1 -1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(25) [pw::Point create]
$_DB(25) setPoint {-1 -1 -1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(26) [pw::Point create]
$_DB(26) setPoint {1 -1 -1}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}

set _DB(27) [pw::Point create]
$_DB(27) setPoint {0 0 0}
#Info: Created 1 point.
pw::Application markUndoLevel {Create Point}


####################################

#curve-1
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(24)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(12)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(36) [pw::Curve create]
$_DB(36) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-2
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(12)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(25)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(37) [pw::Curve create]
$_DB(37) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-3
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(11)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(14)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(38) [pw::Curve create]
$_DB(38) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-4
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(14)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(4)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(39) [pw::Curve create]
$_DB(39) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-5
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(3)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(14)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(40) [pw::Curve create]
$_DB(40) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-6
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(25)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(4)]
$_TMP(PW_1) setCenterPoint {0 0 0} {-1 0 0}
set _DB(41) [pw::Curve create]
$_DB(41) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-7
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) delete
unset _TMP(PW_1)
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(21)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(4)]
$_TMP(PW_1) setCenterPoint {0 0 0} {-1 0 0}
set _DB(42) [pw::Curve create]
$_DB(42) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-8
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(24)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(3)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(43) [pw::Curve create]
$_DB(43) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-9
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(20)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(11)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(44) [pw::Curve create]
$_DB(44) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

##
#curve-10
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(14)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(12)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(45) [pw::Curve create]
$_DB(45) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-11
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(20)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(3)]
$_TMP(PW_1) setCenterPoint {0 0 0} {-1 0 0}
set _DB(46) [pw::Curve create]
$_DB(46) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-12
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(14)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(12)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(47) [pw::Curve create]
$_DB(47) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-13
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(11)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(21)]
$_TMP(PW_1) setCenterPoint {0 0 0} {-1 0 0}
set _DB(48) [pw::Curve create]
$_DB(48) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

##
#curve-14
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(17)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(11)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(49) [pw::Curve create]
$_DB(49) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-15
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(17)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(9)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(50) [pw::Curve create]
$_DB(50) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}


#curve-16
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(9)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(13)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(51) [pw::Curve create]
$_DB(51) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-17
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(13)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(10)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(52) [pw::Curve create]
$_DB(52) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-18
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(10)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(18)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(53) [pw::Curve create]
$_DB(53) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-19
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(18)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(12)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(54) [pw::Curve create]
$_DB(54) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}


#curve-20
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(7)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(16)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(55) [pw::Curve create]
$_DB(55) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-21
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(16)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(8)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(56) [pw::Curve create]
$_DB(56) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-22
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(8)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(18)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(57) [pw::Curve create]
$_DB(57) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-23
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(18)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(6)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(58) [pw::Curve create]
$_DB(58) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-24
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(6)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(15)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(59) [pw::Curve create]
$_DB(59) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-25
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(15)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(5)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(60) [pw::Curve create]
$_DB(60) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-26
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(5)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(17)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(61) [pw::Curve create]
$_DB(61) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-27
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(17)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(7)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(62) [pw::Curve create]
$_DB(62) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

##
#curve-28
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(3)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(15)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(63) [pw::Curve create]
$_DB(63) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-29
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(15)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(1)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(64) [pw::Curve create]
$_DB(64) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-30
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(1)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(13)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(65) [pw::Curve create]
$_DB(65) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-31
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(2)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(13)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(66) [pw::Curve create]
$_DB(66) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-32
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(2)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(16)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(67) [pw::Curve create]
$_DB(67) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-33
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(16)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(4)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(68) [pw::Curve create]
$_DB(68) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

###
#curve-34
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(19)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(9)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(69) [pw::Curve create]
$_DB(69) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-35
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(1)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(23)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(70) [pw::Curve create]
$_DB(70) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-36
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(10)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(13)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(71) [pw::Curve create]
$_DB(71) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

##
#curve-37
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(20)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(5)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(72) [pw::Curve create]
$_DB(72) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}
 
#curve-38
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(21)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(7)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(73) [pw::Curve create]
$_DB(73) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-39
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(5)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(19)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(74) [pw::Curve create]
$_DB(74) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-40
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(19)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(1)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 1 0}
set _DB(75) [pw::Curve create]
$_DB(75) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

###
#curve-41
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(23)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(6)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(76) [pw::Curve create]
$_DB(76) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-42
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(26)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(8)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(77) [pw::Curve create]
$_DB(77) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-43
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(26)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(10)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(78) [pw::Curve create]
$_DB(78) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-44
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(26)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(2)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(79) [pw::Curve create]
$_DB(79) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

###
#curve-45
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(25)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(8)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 -1 0}
set _DB(80) [pw::Curve create]
$_DB(80) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

###

#curve-46
pw::Display setProjection Perspective
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(6)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(24)]
$_TMP(PW_1) setCenterPoint {0 0 0} {-1 0 0}
set _DB(81) [pw::Curve create]
$_DB(81) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}
 
#curve-47
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(23)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(10)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(82) [pw::Curve create]
$_DB(82) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-48
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(22)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(2)]
$_TMP(PW_1) setCenterPoint {0 0 0} {1 0 0}
set _DB(83) [pw::Curve create]
$_DB(83) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}

#curve-49
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(22)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(9)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 -1}
set _DB(84) [pw::Curve create]
$_DB(84) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}
 
#curve-50
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::SegmentCircle create]
$_TMP(PW_1) addPoint [list 0 0 $_DB(22)]
$_TMP(PW_1) addPoint [list 0 0 $_DB(7)]
$_TMP(PW_1) setCenterPoint {0 0 0} {0 0 1}
set _DB(85) [pw::Curve create]
$_DB(85) addSegment $_TMP(PW_1)
unset _TMP(PW_1)
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Create Curve}


pw::Display setProjection Orthonormal

###

set _TMP(PW_1) [pw::Connector createOnDatabase -parametricConnectors Aligned -merge 0 -reject _TMP(unused) [list $_DB(36) $_DB(37) $_DB(38) $_DB(39) $_DB(40) $_DB(41) $_DB(42) $_DB(43) $_DB(44) $_DB(45) $_DB(46) $_DB(47) $_DB(48) $_DB(49) $_DB(50) $_DB(51) $_DB(52) $_DB(53) $_DB(54) $_DB(55) $_DB(56) $_DB(57) $_DB(58) $_DB(59) $_DB(60) $_DB(61) $_DB(62) $_DB(63) $_DB(64) $_DB(65) $_DB(66) $_DB(67) $_DB(68) $_DB(69) $_DB(70) $_DB(71) $_DB(72) $_DB(73) $_DB(74) $_DB(75) $_DB(76) $_DB(77) $_DB(78) $_DB(79) $_DB(80) $_DB(81) $_DB(82) $_DB(83) $_DB(84) $_DB(85)]]
#Info: Created 48 Connectors.
unset _TMP(unused)
unset _TMP(PW_1)
pw::Application markUndoLevel {Connectors On DB Entities}


##
set _CN(1) [pw::GridEntity getByName "con-1"]
set _CN(2) [pw::GridEntity getByName "con-2"]
set _CN(3) [pw::GridEntity getByName "con-3"]
set _CN(4) [pw::GridEntity getByName "con-4"]
set _CN(5) [pw::GridEntity getByName "con-5"]
set _CN(6) [pw::GridEntity getByName "con-6"]
set _CN(7) [pw::GridEntity getByName "con-7"]
set _CN(8) [pw::GridEntity getByName "con-8"]
set _CN(9) [pw::GridEntity getByName "con-9"]
set _CN(10) [pw::GridEntity getByName "con-10"]
set _CN(11) [pw::GridEntity getByName "con-11"]
set _CN(12) [pw::GridEntity getByName "con-12"]
set _CN(13) [pw::GridEntity getByName "con-13"]
set _CN(14) [pw::GridEntity getByName "con-14"]
set _CN(15) [pw::GridEntity getByName "con-15"]
set _CN(16) [pw::GridEntity getByName "con-16"]
set _CN(17) [pw::GridEntity getByName "con-17"]
set _CN(18) [pw::GridEntity getByName "con-18"]
set _CN(19) [pw::GridEntity getByName "con-19"]
set _CN(20) [pw::GridEntity getByName "con-20"]
set _CN(21) [pw::GridEntity getByName "con-21"]
set _CN(22) [pw::GridEntity getByName "con-22"]
set _CN(23) [pw::GridEntity getByName "con-23"]
set _CN(24) [pw::GridEntity getByName "con-24"]
set _CN(25) [pw::GridEntity getByName "con-25"]
set _CN(26) [pw::GridEntity getByName "con-26"]
set _CN(27) [pw::GridEntity getByName "con-27"]
set _CN(28) [pw::GridEntity getByName "con-28"]
set _CN(29) [pw::GridEntity getByName "con-29"]
set _CN(30) [pw::GridEntity getByName "con-30"]
set _CN(31) [pw::GridEntity getByName "con-31"]
set _CN(32) [pw::GridEntity getByName "con-32"]
set _CN(33) [pw::GridEntity getByName "con-33"]
set _CN(34) [pw::GridEntity getByName "con-34"]
set _CN(35) [pw::GridEntity getByName "con-35"]
set _CN(36) [pw::GridEntity getByName "con-36"]
set _CN(37) [pw::GridEntity getByName "con-37"]
set _CN(38) [pw::GridEntity getByName "con-38"]
set _CN(39) [pw::GridEntity getByName "con-39"]
set _CN(40) [pw::GridEntity getByName "con-40"]
set _CN(41) [pw::GridEntity getByName "con-41"]
set _CN(42) [pw::GridEntity getByName "con-42"]
set _CN(43) [pw::GridEntity getByName "con-43"]
set _CN(44) [pw::GridEntity getByName "con-44"]
set _CN(45) [pw::GridEntity getByName "con-45"]
set _CN(46) [pw::GridEntity getByName "con-46"]
set _CN(47) [pw::GridEntity getByName "con-47"]
set _CN(48) [pw::GridEntity getByName "con-48"]

##

set _TMP(mode_1) [pw::Application begin Dimension]
set _TMP(PW_1) [pw::Collection create]
$_TMP(PW_1) set [list $_CN(1) $_CN(2) $_CN(3) $_CN(4) $_CN(5) $_CN(6) $_CN(7) $_CN(8) $_CN(9) $_CN(10) $_CN(11) $_CN(12) $_CN(13) $_CN(14) $_CN(15) $_CN(16) $_CN(17) $_CN(18) $_CN(19) $_CN(20) $_CN(21) $_CN(22) $_CN(23) $_CN(24) $_CN(25) $_CN(26) $_CN(27) $_CN(28) $_CN(29) $_CN(30) $_CN(31) $_CN(32) $_CN(33) $_CN(34) $_CN(35) $_CN(36) $_CN(37) $_CN(38) $_CN(39) $_CN(40) $_CN(41) $_CN(42) $_CN(43) $_CN(44) $_CN(45) $_CN(46) $_CN(47) $_CN(48)]
$_TMP(PW_1) do setDimension -resetDistribution $nds
$_TMP(PW_1) delete
unset _TMP(PW_1)
$_TMP(mode_1) balance -resetGeneralDistributions
$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Dimension}

##

set _TMP(PW_1) [pw::DomainStructured createFromConnectors -reject _TMP(unusedCons) -solid [list $_CN(1) $_CN(2) $_CN(3) $_CN(4) $_CN(5) $_CN(6) $_CN(7) $_CN(8) $_CN(9) $_CN(10) $_CN(11) $_CN(12) $_CN(13) $_CN(14) $_CN(15) $_CN(16) $_CN(17) $_CN(18) $_CN(19) $_CN(20) $_CN(21) $_CN(22) $_CN(23) $_CN(24) $_CN(25) $_CN(26) $_CN(27) $_CN(28) $_CN(29) $_CN(30) $_CN(31) $_CN(32) $_CN(33) $_CN(34) $_CN(35) $_CN(36) $_CN(37) $_CN(38) $_CN(39) $_CN(40) $_CN(41) $_CN(42) $_CN(43) $_CN(44) $_CN(45) $_CN(46) $_CN(47) $_CN(48)]]
#Info: 24 domains created.
unset _TMP(unusedCons)
unset _TMP(PW_1)
pw::Application markUndoLevel {Assemble Domains}

##
set _DM(1) [pw::GridEntity getByName "dom-1"]
set _DM(2) [pw::GridEntity getByName "dom-2"]
set _DM(3) [pw::GridEntity getByName "dom-3"]
set _DM(4) [pw::GridEntity getByName "dom-4"]
set _DM(5) [pw::GridEntity getByName "dom-5"]
set _DM(6) [pw::GridEntity getByName "dom-6"]
set _DM(7) [pw::GridEntity getByName "dom-7"]
set _DM(8) [pw::GridEntity getByName "dom-8"]
set _DM(9) [pw::GridEntity getByName "dom-9"]
set _DM(10) [pw::GridEntity getByName "dom-10"]
set _DM(11) [pw::GridEntity getByName "dom-11"]
set _DM(12) [pw::GridEntity getByName "dom-12"]
set _DM(13) [pw::GridEntity getByName "dom-13"]
set _DM(14) [pw::GridEntity getByName "dom-14"]
set _DM(15) [pw::GridEntity getByName "dom-15"]
set _DM(16) [pw::GridEntity getByName "dom-16"]
set _DM(17) [pw::GridEntity getByName "dom-17"]
set _DM(18) [pw::GridEntity getByName "dom-18"]
set _DM(19) [pw::GridEntity getByName "dom-19"]
set _DM(20) [pw::GridEntity getByName "dom-20"]
set _DM(21) [pw::GridEntity getByName "dom-21"]
set _DM(22) [pw::GridEntity getByName "dom-22"]
set _DM(23) [pw::GridEntity getByName "dom-23"]
set _DM(24) [pw::GridEntity getByName "dom-24"]

## set shell1

set _TMP(PW_1) [pw::BoundaryCondition getByName Unspecified]
set _TMP(PW_2) [pw::BoundaryCondition create]
pw::Application markUndoLevel {Create BC}

set _TMP(PW_3) [pw::BoundaryCondition getByName bc-2]
unset _TMP(PW_2)
$_TMP(PW_3) apply [list $_DM(22) $_DM(24) $_DM(23) $_DM(19) $_DM(9) $_DM(4) $_DM(7) $_DM(11) $_DM(10) $_DM(17) $_DM(2) $_DM(20) $_DM(1) $_DM(3) $_DM(14) $_DM(15) $_DM(12) $_DM(21) $_DM(16) $_DM(6) $_DM(13) $_DM(18) $_DM(8) $_DM(5)]
pw::Application markUndoLevel {Set BC}

$_TMP(PW_3) setPhysicalType -usage CAE Wall
pw::Application markUndoLevel {Change BC Type}

$_TMP(PW_3) setName shell1
pw::Application markUndoLevel {Name BC}

unset _TMP(PW_1)
unset _TMP(PW_3)

## Extrusion
set _TMP(mode_1) [pw::Application begin Create]
set _TMP(PW_1) [pw::FaceStructured createFromDomains [list $_DM(1) $_DM(2) $_DM(3) $_DM(4) $_DM(5) $_DM(6) $_DM(7) $_DM(8) $_DM(9) $_DM(10) $_DM(11) $_DM(12) $_DM(13) $_DM(14) $_DM(15) $_DM(16) $_DM(17) $_DM(18) $_DM(19) $_DM(20) $_DM(21) $_DM(22) $_DM(23) $_DM(24)]]
set _TMP(face_1) [lindex $_TMP(PW_1) 0]
set _TMP(face_2) [lindex $_TMP(PW_1) 1]
set _TMP(face_3) [lindex $_TMP(PW_1) 2]
set _TMP(face_4) [lindex $_TMP(PW_1) 3]
unset _TMP(PW_1)
set _BL(1) [pw::BlockStructured create]
$_BL(1) addFace $_TMP(face_1)
set _BL(2) [pw::BlockStructured create]
$_BL(2) addFace $_TMP(face_2)
set _BL(3) [pw::BlockStructured create]
$_BL(3) addFace $_TMP(face_3)
set _BL(4) [pw::BlockStructured create]
$_BL(4) addFace $_TMP(face_4)
$_TMP(mode_1) end
unset _TMP(mode_1)
set _TMP(mode_1) [pw::Application begin ExtrusionSolver [list $_BL(1) $_BL(2) $_BL(3) $_BL(4)]]
$_TMP(mode_1) setKeepFailingStep true
$_BL(1) setExtrusionSolverAttribute DirectionFlipped 1
$_BL(2) setExtrusionSolverAttribute DirectionFlipped 0
$_BL(3) setExtrusionSolverAttribute DirectionFlipped 1
$_BL(4) setExtrusionSolverAttribute DirectionFlipped 1
$_BL(1) setExtrusionSolverAttribute StopAtHeight Off
$_BL(2) setExtrusionSolverAttribute StopAtHeight Off
$_BL(3) setExtrusionSolverAttribute StopAtHeight Off
$_BL(4) setExtrusionSolverAttribute StopAtHeight Off
$_BL(1) setExtrusionSolverAttribute StopAtHeight [expr $far*sqrt(3)*2]
$_BL(2) setExtrusionSolverAttribute StopAtHeight [expr $far*sqrt(3)*2]
$_BL(3) setExtrusionSolverAttribute StopAtHeight [expr $far*sqrt(3)*2]
$_BL(4) setExtrusionSolverAttribute StopAtHeight [expr $far*sqrt(3)*2]
$_BL(1) setExtrusionSolverAttribute NormalInitialStepSize $dr
$_BL(2) setExtrusionSolverAttribute NormalInitialStepSize $dr
$_BL(3) setExtrusionSolverAttribute NormalInitialStepSize $dr
$_BL(4) setExtrusionSolverAttribute NormalInitialStepSize $dr
$_TMP(mode_1) run 10000

$_TMP(mode_1) end
unset _TMP(mode_1)
pw::Application markUndoLevel {Extrude, Normal}

unset _TMP(face_4)
unset _TMP(face_3)
unset _TMP(face_2)
unset _TMP(face_1)

set _BL(1) [pw::GridEntity getByName "blk-1"]
set _BL(2) [pw::GridEntity getByName "blk-2"]
set _BL(3) [pw::GridEntity getByName "blk-3"]
set _BL(4) [pw::GridEntity getByName "blk-4"]

set _DM(35) [pw::GridEntity getByName "dom-35"]
set _DM(65) [pw::GridEntity getByName "dom-65"]
set _DM(50) [pw::GridEntity getByName "dom-50"]
set _DM(76) [pw::GridEntity getByName "dom-76"]

## boundary conditions: far field

set _TMP(PW_1) [pw::BoundaryCondition getByName Unspecified]
set _TMP(PW_2) [pw::BoundaryCondition getByName shell1]
set _TMP(PW_3) [pw::BoundaryCondition create]
pw::Application markUndoLevel {Create BC}

set _TMP(PW_4) [pw::BoundaryCondition getByName bc-3]
unset _TMP(PW_3)
#$_TMP(PW_4) apply [list [list $_BL(3) $_DM(28)] [list $_BL(2) $_DM(27)] [list $_BL(1) $_DM(25)] [list $_BL(4) $_DM(26)]]

$_TMP(PW_4) apply [list [list $_BL(3) $_DM(65)] [list $_BL(2) $_DM(50)] [list $_BL(4) $_DM(76)] [list $_BL(1) $_DM(35)]]

pw::Application markUndoLevel {Set BC}

$_TMP(PW_4) setName far
pw::Application markUndoLevel {Name BC}

$_TMP(PW_4) setPhysicalType -usage CAE Farfield
pw::Application markUndoLevel {Change BC Type}

unset _TMP(PW_1)
unset _TMP(PW_2)
unset _TMP(PW_4)

### export mesh

#
#export su2 file
#

pw::Application setCAESolver {SU2} 3
pw::Application markUndoLevel {Select Solver}

set _TMP(mode_1) [pw::Application begin CaeExport]
$_TMP(mode_1) addAllEntities

#set _TMP(mode_1) [pw::Application begin CaeExport [pw::Entity sort [list $blk_1 $face_1 $face_2 $face_3 $face_4 $face_9 $face_10 $face_11 $face_12 $face_13 $face_14]]]

set dirsave [pwd]
puts $dirsave
#$_TMP(mode_1) initialize -strict -type CAE "$dirsave/mesh_sphere.su2"
$_TMP(mode_1) initialize -strict -type CAE "mesh_sphere.su2"
$_TMP(mode_1) setAttribute FilePrecision Double
$_TMP(mode_1) verify
$_TMP(mode_1) write
$_TMP(mode_1) end
unset _TMP(mode_1)

#
#export cgns file
#

pw::Application setCAESolver {CGNS} 3
pw::Application markUndoLevel {Select Solver}

#set _TMP(mode_1) [pw::Application begin CaeExport [pw::Entity sort [list $blk_1 $face_1 $face_2 $face_3 $face_4 $face_9 $face_10 $face_11 $face_12 $face_13 $face_14]]]

set _TMP(mode_1) [pw::Application begin CaeExport]
$_TMP(mode_1) addAllEntities

set dirsave [pwd]
puts $dirsave
#$_TMP(mode_1) initialize -strict -type CAE "$dirsave/mesh_sphere.cgns"
$_TMP(mode_1) initialize -strict -type CAE "mesh_sphere.cgns"
$_TMP(mode_1) setAttribute FilePrecision Double
$_TMP(mode_1) verify
$_TMP(mode_1) write
$_TMP(mode_1) end
unset _TMP(mode_1)

}

set nds [lindex $argv 0]
set dr [lindex $argv 1]
set far [lindex $argv 2]

makeSphere $nds $dr $far
#makeSphere 15 0.0001 10

