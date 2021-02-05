# adapted from armadillo:
if(DETECT_HDF5)
  find_package(HDF5 QUIET COMPONENTS C)

  if(NOT HDF5_FOUND)
    # On Debian systems, the HDF5 package has been split into multiple packages
    # so that it is co-installable.  But this may mean that the include files
    # are hidden somewhere very odd that the FindHDF5.cmake script will not
    # find.  Thus, we'll also quickly check pkgconfig to see if there is
    # information on what to use there.
    if (PKG_CONFIG_FOUND)
      pkg_check_modules(HDF5 hdf5)
      # But using pkgconfig is a little weird because HDF5_LIBRARIES won't be
      # filled with exact library paths, like the other scripts.  So instead
      # what we get is HDF5_LIBRARY_DIRS which is the equivalent of what we'd
      # pass to -L.  So we have to add those...
      if (HDF5_FOUND)
        link_directories("${HDF5_LIBRARY_DIRS}")
      endif()
    endif()
  endif()

  message(STATUS "HDF5_FOUND = ${HDF5_FOUND}")
  if(HDF5_FOUND)
    set(EGCPP_USE_HDF5 true)#TODO(mfbolus): prepend project name here
    set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} ${HDF5_INCLUDE_DIRS})
    set(PROJECT_REQUIRED_LIBS ${PROJECT_REQUIRED_LIBS} ${HDF5_LIBRARIES})
    # Since we called HDF5 with no arguments, the script will find only the C
    # bindings.  So HDF5_INCLUDE_DIRS may now contain one or two elements; if it
    # contains two, the first is what the user passed as HDF5_INCLUDE_DIR and we
    # should use that as ARMA_HDF5_INCLUDE_DIR.  Otherwise, the one entry in
    # HDF5_INCLUDE_DIRS is the correct include directory.  So, in either case we
    # can use the first element in the list.  Issue a status message, too, just
    # for good measure.
    # list(GET HDF5_INCLUDE_DIRS 0 ARMA_HDF5_INCLUDE_DIR)
    # message(STATUS "ARMA_HDF5_INCLUDE_DIR = ${ARMA_HDF5_INCLUDE_DIR}")
    message(STATUS "HDF5_INCLUDE_DIRS = ${HDF5_INCLUDE_DIRS}")
    message(STATUS "")
    message(STATUS "*** If use of HDF5 is causing problems,")
    message(STATUS "*** rerun cmake with HDF5 detection disabled:")
    message(STATUS "*** cmake -D DETECT_HDF5=false .")
    message(STATUS "")
  endif()
endif()
