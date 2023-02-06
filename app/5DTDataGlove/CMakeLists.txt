# Copyright: (C) 2022 Istituto Italiano di Tecnologia | Robotics, Brains and Cognitive Science
# Authors: Carlo Mazzola
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

set(appname 5DTDataGlove)

file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.xml
  ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.txt ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*.sh)
file(GLOB scripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*.template  )

yarp_install(FILES ${conf} DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_APPLICATIONS_TEMPLATES_INSTALL_DIR})

