# initialze webtool kit dirs are empty
SET (I_WT_INCLUDE_DIR "")
SET (I_WT_LIB_DIR "")

# if WT_INSTALLED_DIR is defined, set include dir and library dir
if (DEFINED WT_INSTALLED_DIR)
    SET(I_WT_INCLUDE_DIR ${WT_INSTALLED_DIR}/include)
    SET(I_WT_LIB_DIR ${WT_INSTALLED_DIR}/lib)
endif()

# if WT_INCLUDE_DIR is defined, set include dir
if (DEFINED WT_INCLUDE_DIR)
    SET(I_WT_INCLUDE_DIR ${WT_INCLUDE_DIR})
endif()

# if WT_LIB_DIR is defined, set library dir
if (DEFINED WT_LIB_DIR)
    SET(I_WT_LIB_DIR ${WT_LIB_DIR})
endif()

# apply web toolkit dirs to cmake
if (NOT I_WT_INCLUDE_DIR EQUAL "")
    include_directories(${I_WT_INCLUDE_DIR})
endif()
if (NOT I_WT_LIB_DIR EQUAL "")
    link_directories(${I_WT_LIB_DIR})
endif()