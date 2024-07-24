# for M1/M2 mac users, use this FROM instruction instead
# FROM --platform=linux/amd64 ubuntu:20.04

FROM --platform=linux/amd64 ubuntu:20.04

RUN apt-get update && apt-get install -y \
    pkg-config \
    build-essential \  
    libssl-dev \
    zlib1g-dev

# 1 - make directory to run container (directory on container)
RUN mkdir -p /app
# 2 - copy project into newly created directory
COPY . /app
# 3 - CD into new directory for running container
WORKDIR /app
# 4 - compile code
RUN make all
# 5 - run command in docker container once image ran
CMD ["./build/bin/transit_service", "8081", "apps/transit_service/web/"]