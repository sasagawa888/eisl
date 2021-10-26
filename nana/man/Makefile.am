#
# a short makefile
#

CLEANFILES = *~

EXTRA_DIST = nana.1 nana-clg.1 I.3 DI.3 L.3 DL.3 Q.3 Qstl.3 nana.3

man_MANS =  nana.1 nana-clg.1 I.3 DI.3 L.3 DL.3 Q.3 Qstl.3 nana.3 

# We seem to have a problem with automake, if I include nana.1 in the
# man_MANS variable we don't install it. The following dodgey aims
# to fix it.

install-data-local:
	@sect=1;				\
	inst=`echo "nana" | sed '$(transform)'`.1; \
	echo installing nana.1 as $(mandir)/man$$sect/$$inst; \
	$(INSTALL_DATA) $(srcdir)/nana.1 $(mandir)/man$$sect/$$inst

