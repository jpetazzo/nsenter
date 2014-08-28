FROM debian:jessie
ENV VERSION 2.24
RUN apt-get update -q \
 && apt-get install -qy curl build-essential \
 && mkdir /src
WORKDIR /src
RUN curl https://www.kernel.org/pub/linux/utils/util-linux/v$VERSION/util-linux-$VERSION.tar.gz \
     | tar -zxf- \
 && ln -s util-linux-$VERSION util-linux
WORKDIR /src/util-linux
RUN ./configure --without-ncurses \
 && make LDFLAGS=-all-static nsenter
 && cp nsenter /
ADD docker-enter /docker-enter
ADD docker-run /docker-run
ADD installer /installer
CMD /installer
