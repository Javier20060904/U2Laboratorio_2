################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-1265587841:
	@$(MAKE) --no-print-directory -Onone -f aux_files/subdir_rules.mk build-1265587841-inproc

build-1265587841-inproc: ../aux_files/release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/home/marco/ti/ccs/ccs1240/xdctools_3_62_01_16_core/xs" --xdcpath="/home/marco/ti/simplelink_msp432p4_sdk_3_40_01_02/source;/home/marco/ti/simplelink_msp432p4_sdk_3_40_01_02/kernel/tirtos/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P401R -r debug -c "/home/marco/ti/ccs/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1265587841 ../aux_files/release.cfg
configPkg/compiler.opt: build-1265587841
configPkg/: build-1265587841

aux_files/%.obj: ../aux_files/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/marco/ti/ccs/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/marco/ti/workspace_v12/U2Laboratorio_2" --include_path="/home/marco/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="/home/marco/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="/home/marco/ti/ccs/ccs1240/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="aux_files/$(basename $(<F)).d_raw" --obj_directory="aux_files" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


