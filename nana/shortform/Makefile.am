#
# Makefile.am - automake configuration file for the shortform generator
#

EXTRA_DIST = example.c smallex.c

bin_SCRIPTS = nana-sfg nana-sfdir

# 
# example - build a Nana shortform version of the current directory
#
# Note: you need to install the GLOBAL source code to HTML package
#    which is available from:
#
#      Shigio Yamaguchi at http://wafu.netgate.net/tama/unix/global.html
#
#      or at the FreeBSD archives (it is installed by default on FreeBSD)
#
#      or at the nana archive ftp://ftp.cs.ntu.edu.au/pub/nana
#
# Alternatively install your own source to HTML package such as DOC++
# and modify MKHTML
#

MKHTML = cd NANASF; (gtags ; htags) || echo install global

example:
	nana-sfdir 
	$(MKHTML)
	@echo see NANASF/HTML/index.html


