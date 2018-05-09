FROM ubuntu:16.04 as builder
MAINTAINER Luca Lodi <luca1.lodi@mail.polimi.it>

# Install collective-knowledge framework
RUN apt-get update && \
	apt-get install -y python python-pip build-essential git wget && \
	pip install ck

# Download milepost-gcc repo
RUN ck pull repo:reproduce-milepost-project

# Install dependencies to build compiler
RUN apt-get install -y \
	autoconf \
	automake \
	g++ \
	g++-multilib \
	gcc \
	libc6-dev-i386 \
	libcloog-isl-dev \
	libgmp-dev \
	libisl-dev \
	libmpc-dev \
	libmpfr-dev \
	libncurses-dev \
	m4 \
	texinfo \
	uuid-runtime

# Build milepost-gcc
RUN ck install package:compiler-gcc-4.4.4-milepost-src-deps

# Build ctuning-cc to use milepost-gcc
RUN ck install package:compiler-ctuning-cc-2.5-plugins-src && \
	ck install package:compiler-ctuning-cc-2.5-src

# configure ENVironment to use ctuning-cc (and so milepost gcc)
ENV PATH=/root/CK-TOOLS/ctuning-cc-2.5.1-gcc-4.4.4-linux-64/bin:/root/CK-TOOLS/ctuning-cc-2.5.1-gcc-4.4.4-linux-64/src-plat-indep/plugins:/root/CK-TOOLS/plugin-milepost-ctuning-2.5-gcc-4.4.4-linux-64/bin:/root/CK-TOOLS/xsb-3.2-linux-64/3.2/bin:/root/CK-TOOLS/texinfo-4.13-linux-64/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
ENV LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:/root/CK-TOOLS/isl-0.10-linux-64/lib:/root/CK-TOOLS/cloog-0.17.0-linux-64/lib:/root/CK-TOOLS/mpfr-3.1.0-linux-64/lib:/root/CK-TOOLS/gmp-5.0.5-linux-64/lib:
ENV LD_LIBRARY_PATH=/root/CK-TOOLS/isl-0.10-linux-64/lib:/root/CK-TOOLS/cloog-0.17.0-linux-64/lib:/root/CK-TOOLS/mpfr-3.1.0-linux-64/lib:/root/CK-TOOLS/gmp-5.0.5-linux-64/lib:

ENV CTUNING_ANALYSIS_CC=/root/CK-TOOLS/gcc-milepost-4.4.4-linux-64/bin/gcc \ 
    CTUNING_ANALYSIS_CPP=/root/CK-TOOLS/gcc-milepost-4.4.4-linux-64/bin/g++ \ 
    CTUNING_ANALYSIS_FORTRAN=/root/CK-TOOLS/gcc-milepost-4.4.4-linux-64/bin/gfortran \ 
    CTUNING_COMPILER_CC=gcc \ 
    CTUNING_COMPILER_CPP=g++ \ 
    CTUNING_COMPILER_FORTRAN=gfortran

ENV ICI2_PLUGIN_VER=gcc-plugin-ici2 \ 
    ICI_LIB=/root/CK-TOOLS/plugin-milepost-ctuning-2.5-gcc-4.4.4-linux-64/lib \ 
    ICI_PLUGIN_VER=gcc-plugin-ici2 \ 
    ICI_PROG_FEAT_EXT_TOOL=/root/CK-TOOLS/plugin-milepost-ctuning-2.5-gcc-4.4.4-linux-64/bin/featlstn.P \ 
    ICI_PROG_FEAT_PASS=fre

ENV ML_ST_FEAT_TOOL=/root/CK-TOOLS/plugin-milepost-ctuning-2.5-gcc-4.4.4-linux-64/bin/featlstn.P

ENV XSB_DIR=/root/CK-TOOLS/xsb-3.2-linux-64/3.2 \ 
	XSB_DIR_ADD=x86_64-unknown-linux-gnu
	
ENV CCC_COMPILER_FEATURES_ID=129504539516446542 \ 
    CCC_COMPILER_ID=331350613878705696 \ 
    CCC_CTS_DB=fursinne_coptcases \ 
    CCC_CTS_USER=gfursin \ 
    CCC_CTS_URL=cTuning.org/wiki/index.php/Special:CDatabase?request= \
    CCC_ENVIRONMENT_ID=2781195477254972989 \ 
    CCC_ICI_FEATURES_ST_EXT=.ft \ 
    CCC_ICI_FEATURES_ST_EXTRACT_PLUGIN=/root/CK-TOOLS/plugin-milepost-ctuning-2.5-gcc-4.4.4-linux-64/lib/gcc-plugin-ici2-extract-program-static-features.so \ 
    CCC_ICI_FEATURES_ST_FN=ici_features_function \ 
    CCC_ICI_PASSES_EXT=.txt \ 
    CCC_ICI_PASSES_FN=ici_passes_function \ 
    CCC_ICI_PASSES_RECORD_PLUGIN=/root/CK-TOOLS/plugin-milepost-ctuning-2.5-gcc-4.4.4-linux-64/lib/gcc-plugin-ici2-extract-program-structure.so \ 
    CCC_ICI_PLUGINS=ICI_PLUGIN \ 
    CCC_ICI_USE=ICI_USE \ 
    CCC_OPT_ARCH_USE=0 \ 
    CCC_PLUGINS=/root/CK-TOOLS/ctuning-cc-2.5.1-gcc-4.4.4-linux-64/src-plat-indep \ 
    CCC_PLATFORM_ID=2111574609159278179 \
    CCC_ROOT=/root/CK-TOOLS/ctuning-cc-2.5.1-gcc-4.4.4-linux-64 \ 
    CCC_UUID=uuidgen

# Collect binaries and libs in a common place
#RUN mkdir /mybin && cd /mybin && \
#	mv /root/CK-TOOLS/ctuning-cc-2.5.1-gcc-4.4.4-linux-64/bin/* . && \
#	mv /root/CK-TOOLS/ctuning-cc-2.5.1-gcc-4.4.4-linux-64/src-plat-indep/plugins/* . && \
#	mv /root/CK-TOOLS/plugin-milepost-ctuning-2.5-gcc-4.4.4-linux-64/bin/* . && \
#	mv /root/CK-TOOLS/xsb-3.2-linux-64/3.2/bin/* . && \
#	mv /root/CK-TOOLS/texinfo-4.13-linux-64/bin/* .
#RUN mkdir /mylib && cd /mylib && \
#	cp /root/CK-TOOLS/isl-0.10-linux-64/lib/*.* . && \
#	cp /root/CK-TOOLS/cloog-0.17.0-linux-64/lib/*.* . && \
#	cp /root/CK-TOOLS/mpfr-3.1.0-linux-64/lib/*.* . && \
#	cp /root/CK-TOOLS/gmp-5.0.5-linux-64/lib/*.* . && \
#	cp /usr/lib/x86_64-linux-gnu/*.so .

##ROM bash:4.4

#COPY --from=builder /mybin /bin
#COPY --from=builder /mylib /lib
## COPY --from=0 /usr/lib/x86_64-linux-gnu/ /lib

CMD bash
