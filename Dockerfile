# for M1/M2 mac users, use this FROM instruction instead
# FROM --platform=linux/amd64 ubuntu:20.04

FROM --platform=linux/amd64 ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \  
    libssl-dev \
    zlib1g-dev

# 1 - make directory to run container (directory on container)
RUN mkdir -p /run
# 2 - copy project into newly created directory
COPY . /run
# 3 - CD into new directory for running container
WORKDIR /run
# 4 - compile code
RUN make clean
RUN make -j
# 5 - run command in docker container once image ran
CMD ["./build/bin/transit_service", "8081", "apps/transit_service/web/"]