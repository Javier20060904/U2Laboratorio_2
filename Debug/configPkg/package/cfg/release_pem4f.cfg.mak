# invoke SourceDir generated makefile for release.pem4f
release.pem4f: .libraries,release.pem4f
.libraries,release.pem4f: package/cfg/release_pem4f.xdl
	$(MAKE) -f /home/marco/ti/workspace_v12/U2Laboratorio_2/aux_files/src/makefile.libs

clean::
	$(MAKE) -f /home/marco/ti/workspace_v12/U2Laboratorio_2/aux_files/src/makefile.libs clean

