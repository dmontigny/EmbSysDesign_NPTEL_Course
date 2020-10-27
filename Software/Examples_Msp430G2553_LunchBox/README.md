# EmbSysDesign_Online_Course

need to add this to project properties/CCS Build > Steps > Post-build steps:
$(PWD)/../../../BSL_Program/bsl-scripter-linux-64 -cCOM3 -m1 +epvr ${BuildArtifactFileBaseName}.txt
