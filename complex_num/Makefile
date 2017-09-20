SUBDIRS = complex_lib complex_poly_exe

CLEAN_SUBDIRS = $(addprefix clean_, $(SUBDIRS))
.PHONY: subdirs $(SUBDIRS) $(CLEAN_SUBDIRS) clean

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

complex_poly_exe: complex_lib

clean: $(CLEAN_SUBDIRS)

$(CLEAN_SUBDIRS): clean_%:
	$(MAKE) -C $* clean