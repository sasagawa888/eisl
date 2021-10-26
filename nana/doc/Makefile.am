#
# Makefile.am - generates the makefiles for nana/doc
#

info_TEXINFOS = nana.texi

EXTRA_DIST = nana.ps

## maintainer targets

# fixinfo - just do the magic in emacs to setup nana.texi (nodes, menus)

fixinfo:
	emacs -batch nana.texi 	-f texinfo-every-node-update \
				-f texinfo-all-menus-update \
				-f save-buffer \
				-f kill-emacs



