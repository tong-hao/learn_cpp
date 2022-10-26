#!/bin/bash

me=`basename "$0"`
rootdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
sourceroot="${rootdir}/downloads"

# find gcc in vesoft toolset
declare -a dirs=("/opt/vesoft/toolset/gcc/7.5.0" "/opt/vesoft/toolset/clang/10.0.0" )
for dir in ${dirs[@]}; do
   if [ -d "$dir" ]; then
    export PATH=${dir}/bin:${PATH}
    export CC=${dir}/bin/gcc
    export CXX=${dir}/bin/g++
    break
   fi
done

dir="/opt/vesoft/toolset/cmake/bin"
if [ -d $dir ] ; then
   export PATH=$dir:${PATH}
fi

if [[ ! -f $CC ]]
then
  echo "$CC does not exist on your filesystem."
  exit 255
fi

function clean_exec {
  cmd=$*
  eval $cmd
  retcode=$?
  if [ $retcode -ne 0 ]; then
    echo "'${cmd}' exec failed with code $retcode, abort install process!"
    exit 255
  fi
}

function show_help {
  echo "usage: ${me} <install|distclean>"
}

function install {
  # create temporary dir to hold source code
  mkdir -p ${sourceroot}
  pushd ${sourceroot}

  ## boost
  if [ ! -f boost_1_68_0.tar.gz ]; then
    clean_exec wget -O boost_1_68_0.tar.gz https://boostorg.jfrog.io/artifactory/main/release/1.68.0/source/boost_1_68_0.tar.gz
  fi
  clean_exec rm -rf boost_1_68_0
  clean_exec tar vxzf boost_1_68_0.tar.gz

  pushd boost_1_68_0
  clean_exec ./bootstrap.sh --without-libraries=python,contract,context,coroutine,fiber,graph,graph_parallel,mpi,wave,log,test,signals,stacktrace,timer --prefix=${rootdir}/3rd/boost_1_68_0
  clean_exec ./b2 -j8 cxxflags=-fPIC cflags=-fPIC variant=release link=static -a --prefix=${rootdir}/3rd/boost_1_68_0 -j$(nproc) install
  popd

  pushd ${rootdir}/3rd
  clean_exec ln -nsf boost_1_68_0 boost
  popd

  ## gflags
  if [ ! -f gflags-2.2.1.tar.gz ]; then
    clean_exec wget -O gflags-2.2.1.tar.gz https://github.com/gflags/gflags/archive/v2.2.1.tar.gz
  fi
  clean_exec rm -rf gflags-2.2.1
  clean_exec tar vxzf gflags-2.2.1.tar.gz

  pushd gflags-2.2.1
  mkdir -p tmp_build
  pushd tmp_build
  clean_exec CXXFLAGS="-fPIC" cmake .. -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON -DCMAKE_INSTALL_PREFIX=${rootdir}/3rd/gflags-2.2.1
  clean_exec make
  clean_exec make install
  popd
  popd

  pushd ${rootdir}/3rd
  clean_exec ln -nsf gflags-2.2.1 gflags
  popd

  ## libunwind
  if [ ! -f libunwind-1.3.1.tar.gz ]; then
    clean_exec wget https://github.com/libunwind/libunwind/releases/download/v1.3.1/libunwind-1.3.1.tar.gz
  fi
  clean_exec rm -rf libunwind-1.3.1
  clean_exec tar vxzf libunwind-1.3.1.tar.gz

  pushd libunwind-1.3.1
  clean_exec ./configure --with-pic CFLAGS=-g --with-pic --disable-shared --enable-static --disable-documentation --disable-coredump --disable-ptrace --disable-setjmp --disable-tests --disable-debug --disable-minidebuginfo --disable-msabi-support --prefix=${rootdir}/3rd/libunwind-1.3.1
  clean_exec make
  clean_exec make install
  popd

  pushd ${rootdir}/3rd
  clean_exec ln -nsf libunwind-1.3.1 libunwind
  popd

  ## glog
  if [ ! -f glog-0.4.0.tar.gz ]; then
    clean_exec wget -O glog-0.4.0.tar.gz https://github.com/google/glog/archive/v0.4.0.tar.gz
  fi
  clean_exec rm -rf glog-0.4.0
  clean_exec tar vxzf glog-0.4.0.tar.gz
  
  pushd glog-0.4.0
  clean_exec ./autogen.sh
  clean_exec CXXFLAGS='-fPIC' CFLAGS='-fPIC' LDFLAGS="-L${rootdir}/3rd/libunwind/lib" CPPFLAGS="-I${rootdir}/3rd/libunwind/include" ./configure --enable-shared=no --enable-static=yes --with-gflags=${rootdir}/3rd/gflags-2.2.1 --prefix=${rootdir}/3rd/glog-0.4.0
  clean_exec GFLAGS_LIBS='' make
  clean_exec make install
  popd

  pushd ${rootdir}/3rd
  clean_exec ln -nsf glog-0.4.0 glog
  popd

  ## googletest
  if [ ! -f googletest-1.8.1.tar.gz ]; then
    clean_exec wget -O googletest-1.8.1.tar.gz https://github.com/google/googletest/archive/release-1.8.1.tar.gz
  fi
  clean_exec tar vxzf googletest-1.8.1.tar.gz -C ${rootdir}/3rd
  pushd ${rootdir}/3rd
  clean_exec ln -nsf googletest-release-1.8.1 googletest
  popd

  ## yas
  if [ ! -f yas-7.0.2.tar.gz ]; then
    clean_exec wget -O yas-7.0.2.tar.gz https://github.com/niXman/yas/archive/7.0.2.tar.gz
  fi
  clean_exec tar vxzf yas-7.0.2.tar.gz -C ${rootdir}/3rd
  pushd ${rootdir}/3rd
  clean_exec ln -nsf yas-7.0.2 yas
  popd

  ## sparsehash
  if [ ! -f sparsehash-2.0.3.tar.gz ]; then
    clean_exec wget -O sparsehash-2.0.3.tar.gz https://github.com/sparsehash/sparsehash/archive/sparsehash-2.0.3.tar.gz
  fi
  clean_exec rm -rf sparsehash-sparsehash-2.0.3
  clean_exec tar vxzf sparsehash-2.0.3.tar.gz

  pushd sparsehash-sparsehash-2.0.3
  clean_exec ./configure --prefix=${rootdir}/3rd/sparsehash-2.0.3
  clean_exec make
  clean_exec make install
  popd

  pushd ${rootdir}/3rd
  clean_exec ln -nsf sparsehash-2.0.3 sparsehash
  popd

  ## jni TODO

  ## hadoop TODO
  # if [ ! -f release-2.7.4.tar.gz ]; then
  #   clean_exec wget https://github.com/apache/hadoop/archive/rel/release-2.7.4.tar.gz
  # fi
  # clean_exec tar vxzf release-2.7.4.tar.gz
  # 
  # pushd hadoop-rel-release-2.7.4
  # mvn package -Pdist,native -DskipTests -Dtar
  # popd

  ## jemalloc
  if [ ! -f jemalloc.5.2.0.tar.gz ]; then
    clean_exec wget -O jemalloc.5.2.0.tar.gz https://github.com/jemalloc/jemalloc/archive/5.2.0.tar.gz
  fi
  clean_exec rm -rf jemalloc-5.2.0
  clean_exec tar vxzf jemalloc.5.2.0.tar.gz

  pushd jemalloc-5.2.0
  clean_exec ./autogen.sh
  clean_exec CXXFLAGS='-fPIC' CFLAGS='-fPIC' ./configure --enable-shared=no --enable-static=yes --prefix=${rootdir}/3rd/jemalloc-5.2.0
  clean_exec make
  clean_exec make install
  popd

  pushd ${rootdir}/3rd
  clean_exec ln -nsf jemalloc-5.2.0 jemalloc 
  popd

  ## mpich
  if [ ! -f mpich-3.2.1.tar.gz ]; then
    clean_exec wget --no-check-certificate -O mpich-3.2.1.tar.gz http://www.mpich.org/static/downloads/3.2.1/mpich-3.2.1.tar.gz
  fi
  clean_exec rm -rf mpich-3.2.1
  clean_exec tar vxzf mpich-3.2.1.tar.gz

  pushd mpich-3.2.1
  clean_exec ./configure --with-pic --enable-static --disable-shared --disable-fortran --disable-mpi-fortran --enable-mpi-thread-mutliple --prefix=${rootdir}/3rd/mpich-3.2.1
  clean_exec make -j$(nproc)
  clean_exec make install
  popd

  pushd ${rootdir}/3rd
  clean_exec ln -nsf mpich-3.2.1 mpich
  popd

  ## nebula-cpp
  if [ ! -d nebula-cpp ]; then
    clean_exec git clone -b master https://github.com/vesoft-inc/nebula-cpp.git
  fi

  pushd nebula-cpp
  clean_exec mkdir -p build
  pushd build
  clean_exec cmake -DCMAKE_INSTALL_PREFIX=${rootdir}/3rd/nebula-cpp ..
  clean_exec make -j$(nproc)
  clean_exec make install
  popd
  popd

  pushd ${rootdir}/3rd
  popd

  popd
  echo "build 3rd done, you can remove .downloads now."
}

function distclean {
  pushd ${rootdir}/3rd
  clean_exec rm boost boost_1_68_0 -rf
  clean_exec rm gflags gflags-2.2.1 -rf
  clean_exec rm libunwind libunwind-1.3.1 -rf 
  clean_exec rm glog glog-0.4.0 -rf
  clean_exec rm googletest googletest-release-1.8.1 -rf
  clean_exec rm yas yas-7.0.2 -rf
  clean_exec rm sparsehash sparsehash-2.0.3 -rf
  clean_exec rm jemalloc jemalloc-5.2.0 -rf 
  clean_exec rm mpich mpich-3.2.1 -rf 
  popd

  rm ${sourceroot} -rf

  echo "distclean 3rd done!"
}

if [ x$1 != x ]; then
  if [ $1 = "install" ]; then
    install; exit 0
  elif [ $1 = "distclean" ]; then
    distclean; exit 0
  else
    show_help; exit 1
  fi
else
  show_help; exit 1
fi


