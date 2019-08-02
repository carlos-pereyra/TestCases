#
# author: carlos pereyra
# setup: make sure to set your alias
#           alias pointwise='/path/to/pointwise'
#
# usage: pointwise -b <*.glf> <unit diameter> <far/diameter>
#
#

package require PWI_Glyph
package require PWI_Glyph 2

proc defaults { } {
    #
    #set defaults
    #

    #pw::Connector setDefault Dimension 50
    pw::Connector setCalculateDimensionMethod Spacing
    pw::Connector setCalculateDimensionSpacing 0.10000000000000001
    pw::Application setGridPreference Unstructured
    pw::DomainUnstructured setDefault Algorithm AdvancingFrontOrtho
    #pw::DomainUnstructured setDefault Algorithm Delaunay
    pw::DomainUnstructured setDefault IsoCellType TriangleQuad
    pw::DomainUnstructured setDefault TRexGrowthRate 1.1000000000000001
    pw::DomainUnstructured setDefault TRexMaximumLayers 15
    pw::DomainUnstructured setDefault TRexFullLayers 1
    pw::DomainUnstructured setDefault QuadMaximumIncludedAngle 170
    pw::BlockUnstructured setDefault TRexMaximumLayers 25
    pw::BlockUnstructured setDefault TRexFullLayers 1
    pw::BlockUnstructured setDefault TRexGrowthRate 1.1000000000000001
    pw::BlockUnstructured setDefault TRexCollisionBuffer 3
    pw::BlockUnstructured setDefault TRexSkewCriteriaMaximumAngle 170

}

proc makeASphere {x y z r} {
    #
    #create a sphere
    #

    set _TMP(mode_1) [pw::Application begin Create]
    set _TMP(PW_1) [pw::Shape create]
    $_TMP(PW_1) sphere -radius $r -baseAngle 0 -topAngle 180
    $_TMP(PW_1) setTransform [list -1 0 -0 0 -0 -0 1 0 0 1 0 0 $x $y $z 1]
    $_TMP(PW_1) setPivot Center
    $_TMP(PW_1) setSectionMinimum 0
    $_TMP(PW_1) setSectionMaximum 360
    $_TMP(PW_1) setSidesType Plane
    $_TMP(PW_1) setBaseType Plane
    $_TMP(PW_1) setTopType Plane
    #set primative [$_TMP(PW_1) getPrimitive]
    $_TMP(PW_1) setEnclosingEntities {}
    set _TMP(PW_2) [$_TMP(PW_1) createModels]

    #
    #delete sphere stuff
    #

    unset _TMP(PW_2)
    pw::Entity delete $_TMP(PW_1)
    unset _TMP(PW_1)
    $_TMP(mode_1) end
    unset _TMP(mode_1)
    pw::Application markUndoLevel {Create Shape}

}

proc makeSphereMesh {diam far} {

    set radius [expr $diam/2.]

    #=======================================

    defaults

    makeASphere 0 0 0 $radius
    #makeASphere $separation 0 0 $radius

    #=======================================

    #
    #get quilts 1
    #
    set mdl_1 [pw::DatabaseEntity getByName "model-1"]
    set q_1 [$mdl_1 getQuilts]
    set _TMP(PW_1) [pw::DomainUnstructured createOnDatabase -parametricConnectors Aligned -merge 0 -joinConnectors 0 -reject _TMP(unused) [list $mdl_1 $q_1]]

    #
    #get surfaces 1
    #
    set face_1 [pw::GridEntity getByName "dom-1"]
    set face_2 [pw::GridEntity getByName "dom-2"]
    set face_3 [pw::GridEntity getByName "dom-3"]
    set face_4 [pw::GridEntity getByName "dom-4"]

if 0 {
    #
    #get quilts 2
    #
    set mdl_2 [pw::DatabaseEntity getByName "model-2"]
    set q_2 [$mdl_2 getQuilts]
    set _TMP(PW_2) [pw::DomainUnstructured createOnDatabase -parametricConnectors Aligned -merge 0 -joinConnectors 0 -reject _TMP(unused) [list $mdl_2 $q_2]]

    #
    #get surfaces 2
    #
    set face_5 [pw::GridEntity getByName "dom-5"]
    set face_6 [pw::GridEntity getByName "dom-6"]
    set face_7 [pw::GridEntity getByName "dom-7"]
    set face_8 [pw::GridEntity getByName "dom-8"]
}
    #=======================================

    #
    #set far-field
    #

    set dim_x [expr 2*$diam*$far]
    set dim_y [expr 2*$diam*$far]
    set dim_z [expr 2*$diam*$far]

    #set _TMP(mode_1) [pw::Application begin Modify [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8]]
    set _TMP(mode_1) [pw::Application begin Modify [list $face_1 $face_2 $face_3 $face_4]]
    set _TMP(PW_1) [pw::GridShape create]
    set _TMP(PW_2) [pw::TRexCondition create]
    $_TMP(PW_2) setConditionType Match
    $_TMP(PW_2) setName BuildBlocksMatch
    $_TMP(PW_2) setAdaptation On
    unset _TMP(PW_2)
    set _TMP(PW_2) [pw::TRexCondition create]
    $_TMP(PW_2) setConditionType Off
    $_TMP(PW_2) setName BuildBlocksOff
    $_TMP(PW_2) setAdaptation On
    unset _TMP(PW_2)
    pw::Display resetView -Z
    $_TMP(PW_1) box -width $dim_z -height $dim_y -length $dim_x
    $_TMP(PW_1) setGridType Unstructured
    $_TMP(PW_1) setTransform [list 0 1 0 0 0 0 1 0 1 0 0 0 -$far 0 0 1]
    $_TMP(PW_1) setSectionQuadrants 4
    $_TMP(PW_1) setIncludeEnclosingEntitiesInBlock 1
    $_TMP(PW_1) setGridBoundary FromSizeField
    $_TMP(PW_1) setSizeFieldDecay [pw::GridEntity getDefault SizeFieldDecay]
    $_TMP(PW_1) setSizeFieldBackgroundSpacing 0.5
    #$_TMP(PW_1) setEnclosingEntities [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8]
    $_TMP(PW_1) setEnclosingEntities [list $face_1 $face_2 $face_3 $face_4]
    $_TMP(PW_1) clearSizeFieldEntities
    #$_TMP(PW_1) includeSizeFieldEntity [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8] true
    $_TMP(PW_1) includeSizeFieldEntity [list $face_1 $face_2 $face_3 $face_4] true
    $_TMP(PW_1) updateGridEntities -updateBlockAttributes

    set _TMP(blocks) [$_TMP(PW_1) getGridEntities -type pw::Block]
    set _TMP(blockCollection) [pw::Collection create]
    $_TMP(blockCollection) set $_TMP(blocks)

    $_TMP(blockCollection) do setUnstructuredSolverAttribute TRexPushAttributes 1
    $_TMP(blockCollection) do setUnstructuredSolverAttribute TRexMaximumLayers 20
    $_TMP(blockCollection) do setUnstructuredSolverAttribute TRexFullLayers 1
    $_TMP(blockCollection) do setUnstructuredSolverAttribute TRexGrowthRate 1.1000000000000001
    set _TMP(bc) [pw::TRexCondition getByName BuildBlocksMatch]
    set _TMP(doms) [$_TMP(PW_1) getBlockRegisters Symmetry]
    $_TMP(bc) apply $_TMP(doms)

    unset _TMP(bc)
    unset _TMP(doms)
    set _TMP(bc) [pw::TRexCondition getByName BuildBlocksOff]
    set _TMP(doms) [$_TMP(PW_1) getBlockRegisters Other]
    $_TMP(bc) apply $_TMP(doms)

    unset _TMP(bc)
    unset _TMP(doms)
    $_TMP(blockCollection) do pushAttributes
    $_TMP(blockCollection) do boundaryAdaptation
    $_TMP(blockCollection) delete
    unset _TMP(blocks)
    unset _TMP(blockCollection)
    unset _TMP(PW_1)
    $_TMP(mode_1) end
    unset _TMP(mode_1)
    pw::Application markUndoLevel {Build Blocks}

    #=======================================

    #
    #get far-field surfaces
    #
if 0 {
    set face_9 [pw::GridEntity getByName "dom-9"]
    set face_10 [pw::GridEntity getByName "dom-10"]
    set face_11 [pw::GridEntity getByName "dom-11"]
    set face_12 [pw::GridEntity getByName "dom-12"]
    set face_13 [pw::GridEntity getByName "dom-13"]
    set face_14 [pw::GridEntity getByName "dom-14"]
}
    set face_9 [pw::GridEntity getByName "dom-5"]
    set face_10 [pw::GridEntity getByName "dom-6"]
    set face_11 [pw::GridEntity getByName "dom-7"]
    set face_12 [pw::GridEntity getByName "dom-8"]
    set face_13 [pw::GridEntity getByName "dom-9"]
    set face_14 [pw::GridEntity getByName "dom-10"]

    #
    #visualization settings
    #
    set _TMP(PW_1) [pw::Collection create]
    $_TMP(PW_1) set [list $face_10 $face_11 $face_12 $face_13 $face_14]
    $_TMP(PW_1) do setRenderAttribute LineMode Boundary
    $_TMP(PW_1) delete
    unset _TMP(PW_1)
    pw::Application markUndoLevel {Modify Entity Display}

if 0 {
    #
    #sphere shell settings
    #
    set _TMP(PW_1) [pw::Collection create]
    $_TMP(PW_1) set [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8]
    $_TMP(PW_1) do setRenderAttribute FillMode Shaded
    $_TMP(PW_1) delete
    unset _TMP(PW_1)
    pw::Application markUndoLevel {Modify Entity Display}

    set _TMP(PW_1) [pw::Collection create]
    $_TMP(PW_1) set [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8]
    $_TMP(PW_1) do setRenderAttribute ColorMode Entity
    $_TMP(PW_1) delete
    unset _TMP(PW_1)
    set _TMP(PW_1) [pw::Collection create]
    $_TMP(PW_1) set [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8]
    $_TMP(PW_1) do setColor 0x0031b5d7
    $_TMP(PW_1) delete
    unset _TMP(PW_1)
    pw::Application markUndoLevel {Modify Entity Display}
}
    #=======================================

    #
    #get block
    #

    set blk_1 [pw::GridEntity getByName "blk-1"]

    #
    #generate mesh
    #

    # Apply boundary condition bc-4 to 8 domains.

    set _TMP(mode_1) [pw::Application begin UnstructuredSolver [list $blk_1]]
    set _TMP(PW_1) [pw::TRexCondition getByName {Unspecified}]
    set _TMP(PW_2) [pw::TRexCondition getByName {BuildBlocksMatch}]
    set _TMP(PW_3) [pw::TRexCondition getByName {BuildBlocksOff}]
    set _TMP(PW_4) [pw::TRexCondition create]
    set _TMP(PW_5) [pw::TRexCondition getByName {bc-4}]
    unset _TMP(PW_4)

    $_TMP(PW_5) apply [list [list $blk_1 $face_1 Opposite] [list $blk_1 $face_2 Opposite] [list $blk_1 $face_3 Opposite] [list $blk_1 $face_4 Opposite]]
    #$_TMP(PW_5) apply [list [list $blk_1 $face_1 Opposite] [list $blk_1 $face_2 Opposite] [list $blk_1 $face_3 Opposite] [list $blk_1 $face_4 Opposite] [list $blk_1 $face_5 Opposite] [list $blk_1 $face_6 Opposite] [list $blk_1 $face_7 Opposite] [list $blk_1 $face_8 Opposite]]
    #$_TMP(PW_5) apply [list [list $blk_1 $face_4 Opposite] [list $blk_1 $face_5 Opposite] [list $blk_1 $face_6 Opposite] [list $blk_1 $face_7 Opposite] [list $blk_1 $face_11 Opposite] [list $blk_1 $face_12 Opposite] [list $blk_1 $face_13 Opposite] [list $blk_1 $face_14 Opposite]]
    $_TMP(PW_5) setConditionType {Wall}

    # Apply boundary condition bc-4 to 8 domains

    #set _TMP(PW_6) [pw::TRexCondition create]
    #set _TMP(PW_7) [pw::TRexCondition getByName {bc-5}]
    #unset _TMP(PW_6)
    #$_TMP(PW_7) apply [list [list $blk_1 $face_9 Opposite] [list $blk_1 $face_10 Same] [list $blk_1 $face_11 Same] [list $blk_1 $face_12 Same] [list $blk_1 $face_13 Same] [list $blk_1 $face_14 Same]]
    #$_TMP(PW_7) apply [list [list $blk_1 $face_10 Opposite] [list $blk_1 $face_1 Same] [list $blk_1 $face_3 Same] [list $blk_1 $face_1 Same] [list $blk_1 $face_9 Same] [list $blk_1 $face_8 Same]]

    # Apply boundary condition bc-5 to 6 domains.

    #$_TMP(PW_7) setConditionType {Match}

    #
    # run
    #

    $_TMP(mode_1) setStopWhenFullLayersNotMet true
    $_TMP(mode_1) setAllowIncomplete true
    $_TMP(mode_1) run Initialize

    set _TMP(exam_1) [pw::Examine create "BlockCellType"]
    $_TMP(exam_1) addEntity [list $blk_1]
    $_TMP(exam_1) examine
    pw::CutPlane applyMetric "BlockCellType"

    #
    #end mesh generation
    #

    $_TMP(mode_1) end
    unset _TMP(mode_1)
    pw::Application markUndoLevel {Solve}

    unset _TMP(PW_1)
    unset _TMP(PW_2)
    unset _TMP(PW_3)
    unset _TMP(PW_5)
    #unset _TMP(PW_7)

    #
    #set visual angle
    #

    pw::Display resetView -Z

    #=======================================

    #
    #set boundary names
    #

    #
    # set shell 1 name
    #

    set _TMP(PW_1) [pw::BoundaryCondition getByName Unspecified]
    set _TMP(PW_2) [pw::BoundaryCondition create]
    pw::Application markUndoLevel {Create BC}

    set _TMP(PW_3) [pw::BoundaryCondition getByName bc-2]
    #unset _TMP(PW_2)
    $_TMP(PW_3) apply [list [list $blk_1 $face_1] [list $blk_1 $face_2] [list $blk_1 $face_3] [list $blk_1 $face_4]]
    pw::Application markUndoLevel {Set BC}

    $_TMP(PW_3) setName shell1
    pw::Application markUndoLevel {Name BC}

    $_TMP(PW_3) setPhysicalType -usage CAE Wall
    pw::Application markUndoLevel {Change BC Type}

    unset _TMP(PW_1)
    unset _TMP(PW_2)
    unset _TMP(PW_3)

if 0 {
    #
    # set shell 2 name
    #

    set _TMP(PW_1) [pw::BoundaryCondition getByName Unspecified]
    set _TMP(PW_2) [pw::BoundaryCondition create]
    pw::Application markUndoLevel {Create BC}

    set _TMP(PW_3) [pw::BoundaryCondition getByName bc-3]
    #unset _TMP(PW_2)
    $_TMP(PW_3) apply [list [list $blk_1 $face_5] [list $blk_1 $face_6] [list $blk_1 $face_7] [list $blk_1 $face_8]]
    pw::Application markUndoLevel {Set BC}

    $_TMP(PW_3) setName shell2
    pw::Application markUndoLevel {Name BC}

    $_TMP(PW_3) setPhysicalType -usage CAE Wall
    pw::Application markUndoLevel {Change BC Type}

    unset _TMP(PW_1)
    unset _TMP(PW_2)
    unset _TMP(PW_3)
}
    #
    # set far-field name
    #

    set _TMP(PW_1) [pw::BoundaryCondition getByName Unspecified]
    set _TMP(PW_2) [pw::BoundaryCondition create]
    pw::Application markUndoLevel {Create BC}

    set _TMP(PW_4) [pw::BoundaryCondition getByName bc-3]
    $_TMP(PW_4) apply [list [list $blk_1 $face_9] [list $blk_1 $face_14] [list $blk_1 $face_11] [list $blk_1 $face_12] [list $blk_1 $face_13] [list $blk_1 $face_10]]
    pw::Application markUndoLevel {Set BC}

    $_TMP(PW_4) setPhysicalType -usage CAE Farfield
    pw::Application markUndoLevel {Change BC Type}

    $_TMP(PW_4) setName far
    pw::Application markUndoLevel {Name BC}

    unset _TMP(PW_1)
    unset _TMP(PW_2)
    unset _TMP(PW_4)

    #=======================================

    #
    #export su2 file
    #

    pw::Application setCAESolver {SU2} 3
    pw::Application markUndoLevel {Select Solver}


    set _TMP(mode_1) [pw::Application begin CaeExport [pw::Entity sort [list $blk_1 $face_1 $face_2 $face_3 $face_4 $face_9 $face_10 $face_11 $face_12 $face_13 $face_14]]]
    #set _TMP(mode_1) [pw::Application begin CaeExport [pw::Entity sort [list $blk_1 $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8 $face_9 $face_10 $face_11 $face_12 $face_13 $face_14]]]

    set dirsave [pwd]
    puts $dirsave
    $_TMP(mode_1) initialize -strict -type CAE "$dirsave/mesh_sphere.su2"
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

    set _TMP(mode_1) [pw::Application begin CaeExport [pw::Entity sort [list $blk_1 $face_1 $face_2 $face_3 $face_4 $face_9 $face_10 $face_11 $face_12 $face_13 $face_14]]]
    #set _TMP(mode_1) [pw::Application begin CaeExport [pw::Entity sort [list $blk_1 $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8 $face_9 $face_10 $face_11 $face_12 $face_13 $face_14]]]

    set dirsave [pwd]
    puts $dirsave
    $_TMP(mode_1) initialize -strict -type CAE "$dirsave/mesh_sphere.cgns"
    $_TMP(mode_1) setAttribute FilePrecision Double
    $_TMP(mode_1) verify
    $_TMP(mode_1) write
    $_TMP(mode_1) end
    unset _TMP(mode_1)

}

set diameter [lindex $argv 0]
set far [lindex $argv 1]

makeSphereMesh $diameter $far
