#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../micromouse_exercises.X/IOconfig.c ../micromouse_exercises.X/myPWM.c ../micromouse_exercises.X/main.c myTimers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1379227414/IOconfig.o ${OBJECTDIR}/_ext/1379227414/myPWM.o ${OBJECTDIR}/_ext/1379227414/main.o ${OBJECTDIR}/myTimers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1379227414/IOconfig.o.d ${OBJECTDIR}/_ext/1379227414/myPWM.o.d ${OBJECTDIR}/_ext/1379227414/main.o.d ${OBJECTDIR}/myTimers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1379227414/IOconfig.o ${OBJECTDIR}/_ext/1379227414/myPWM.o ${OBJECTDIR}/_ext/1379227414/main.o ${OBJECTDIR}/myTimers.o

# Source Files
SOURCEFILES=../micromouse_exercises.X/IOconfig.c ../micromouse_exercises.X/myPWM.c ../micromouse_exercises.X/main.c myTimers.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1379227414/IOconfig.o: ../micromouse_exercises.X/IOconfig.c  .generated_files/flags/default/8da81c4ffa1eaae08390e14d365df63759ca1e35 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1379227414" 
	@${RM} ${OBJECTDIR}/_ext/1379227414/IOconfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1379227414/IOconfig.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../micromouse_exercises.X/IOconfig.c  -o ${OBJECTDIR}/_ext/1379227414/IOconfig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1379227414/IOconfig.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1379227414/myPWM.o: ../micromouse_exercises.X/myPWM.c  .generated_files/flags/default/f9e1155ebbffdb252c7a088480d103ad13ab5fc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1379227414" 
	@${RM} ${OBJECTDIR}/_ext/1379227414/myPWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1379227414/myPWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../micromouse_exercises.X/myPWM.c  -o ${OBJECTDIR}/_ext/1379227414/myPWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1379227414/myPWM.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1379227414/main.o: ../micromouse_exercises.X/main.c  .generated_files/flags/default/85f7ecbb5935cd4adfe688f12959966a50bab5b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1379227414" 
	@${RM} ${OBJECTDIR}/_ext/1379227414/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1379227414/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../micromouse_exercises.X/main.c  -o ${OBJECTDIR}/_ext/1379227414/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1379227414/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/myTimers.o: myTimers.c  .generated_files/flags/default/3250f74719d144725f95785fac51cf612e7dbb56 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/myTimers.o.d 
	@${RM} ${OBJECTDIR}/myTimers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  myTimers.c  -o ${OBJECTDIR}/myTimers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/myTimers.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1379227414/IOconfig.o: ../micromouse_exercises.X/IOconfig.c  .generated_files/flags/default/895593eaa4cd0fd515e4f3b34245faad52679411 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1379227414" 
	@${RM} ${OBJECTDIR}/_ext/1379227414/IOconfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1379227414/IOconfig.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../micromouse_exercises.X/IOconfig.c  -o ${OBJECTDIR}/_ext/1379227414/IOconfig.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1379227414/IOconfig.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1379227414/myPWM.o: ../micromouse_exercises.X/myPWM.c  .generated_files/flags/default/16868fc20710b820d6abc2412906cbb61fd2b26c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1379227414" 
	@${RM} ${OBJECTDIR}/_ext/1379227414/myPWM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1379227414/myPWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../micromouse_exercises.X/myPWM.c  -o ${OBJECTDIR}/_ext/1379227414/myPWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1379227414/myPWM.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1379227414/main.o: ../micromouse_exercises.X/main.c  .generated_files/flags/default/b5b7bc1d692eaff0a70b12114c58871ac4a0937b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1379227414" 
	@${RM} ${OBJECTDIR}/_ext/1379227414/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1379227414/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../micromouse_exercises.X/main.c  -o ${OBJECTDIR}/_ext/1379227414/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1379227414/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/myTimers.o: myTimers.c  .generated_files/flags/default/20e820badfdd4c8e8d9e2df7439251139770a7b8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/myTimers.o.d 
	@${RM} ${OBJECTDIR}/myTimers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  myTimers.c  -o ${OBJECTDIR}/myTimers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/myTimers.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/micromouse_exercises.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
