FROM debian:jessie
ENV VERSION 2.26
RUN apt-get update -q
RUN apt-get install -qy curl build-essential
RUN mkdir /src
WORKDIR /src
RUN curl https://www.kernel.org/pub/linux/utils/util-linux/v$VERSION/util-linux-$VERSION.tar.gz \
     | tar -zxf-
RUN ln -s util-linux-$VERSION util-linux
WORKDIR /src/util-linux
RUN ./configure --without-ncurses
RUN make LDFLAGS=-all-static nsenter
RUN cp nsenter /
ADD docker-enter /docker-enter
ADD installer /installer
CMD /installer
# Now build the importenv helper
WORKDIR /src
ADD importenv.c /src/importenv.c
RUN make LDFLAGS=-static CFLAGS=-Wall importenv
RUN cp importenv /
