package require PWI_Glyph 2

proc makeSphere { } {

    #=======================================

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
    pw::DomainUnstructured setDefault TRexMaximumLayers 10
    pw::DomainUnstructured setDefault TRexFullLayers 1
    pw::DomainUnstructured setDefault QuadMaximumIncludedAngle 170
    pw::BlockUnstructured setDefault TRexMaximumLayers 20
    pw::BlockUnstructured setDefault TRexFullLayers 1
    pw::BlockUnstructured setDefault TRexGrowthRate 1.1000000000000001
    pw::BlockUnstructured setDefault TRexCollisionBuffer 3
    pw::BlockUnstructured setDefault TRexSkewCriteriaMaximumAngle 170

    #=======================================

    #
    #create sphere 1
    #
    set _TMP(mode_1) [pw::Application begin Create]
    set _TMP(PW_1) [pw::Shape create]
    $_TMP(PW_1) sphere -radius 1 -baseAngle 0 -topAngle 180
    $_TMP(PW_1) setTransform [list -1 0 -0 0 -0 -0 1 0 0 1 0 0 0 0 0 1]
    $_TMP(PW_1) setPivot Center
    $_TMP(PW_1) setSectionMinimum 0
    $_TMP(PW_1) setSectionMaximum 360
    $_TMP(PW_1) setSidesType Plane
    $_TMP(PW_1) setBaseType Plane
    $_TMP(PW_1) setTopType Plane
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

    #
    #create sphere 2
    #
    set _TMP(mode_1) [pw::Application begin Create]
    set _TMP(PW_1) [pw::Shape create]
    $_TMP(PW_1) sphere -radius 1 -baseAngle 0 -topAngle 180
    $_TMP(PW_1) setTransform [list -1 0 -0 0 -0 -0 1 0 0 1 0 0 3 0 0 1]
    $_TMP(PW_1) setPivot Center
    $_TMP(PW_1) setSectionMinimum 0
    $_TMP(PW_1) setSectionMaximum 360
    $_TMP(PW_1) setSidesType Plane
    $_TMP(PW_1) setBaseType Plane
    $_TMP(PW_1) setTopType Plane
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

    #=======================================

    #
    #set far-field
    #
    set _TMP(mode_1) [pw::Application begin Modify [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8]]
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
    $_TMP(PW_1) box -width 14 -height 13.9989724324 -length 17
    $_TMP(PW_1) setGridType Unstructured
    $_TMP(PW_1) setTransform [list 0 1 0 0 0 0 1 0 1 0 0 0 -7 0 0 1]
    $_TMP(PW_1) setSectionQuadrants 4
    $_TMP(PW_1) setIncludeEnclosingEntitiesInBlock 1
    $_TMP(PW_1) setGridBoundary FromSizeField
    $_TMP(PW_1) setSizeFieldDecay [pw::GridEntity getDefault SizeFieldDecay]
    $_TMP(PW_1) setSizeFieldBackgroundSpacing 0.5
    $_TMP(PW_1) setEnclosingEntities [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8]
    $_TMP(PW_1) clearSizeFieldEntities
    $_TMP(PW_1) includeSizeFieldEntity [list $face_1 $face_2 $face_3 $face_4 $face_5 $face_6 $face_7 $face_8] true
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
    set face_10 [pw::GridEntity getByName "dom-10"]
    set face_11 [pw::GridEntity getByName "dom-11"]
    set face_12 [pw::GridEntity getByName "dom-12"]
    set face_13 [pw::GridEntity getByName "dom-13"]
    set face_14 [pw::GridEntity getByName "dom-14"]

    #
    #visualization settings
    #
    set _TMP(PW_1) [pw::Collection create]
    $_TMP(PW_1) set [list $face_10 $face_11 $face_12 $face_13 $face_14]
    $_TMP(PW_1) do setRenderAttribute LineMode Boundary
    $_TMP(PW_1) delete
    unset _TMP(PW_1)
    pw::Application markUndoLevel {Modify Entity Display}

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

    #
    #set visual angle
    #
    pw::Display resetView -Z
}


makeSphere

