# our local base image
FROM ubuntu

WORKDIR /usr/src/app
COPY . .

# install build dependencies
RUN apt-get update && apt-get install -y gcc rsync zip openssh-server make

CMD [ "" ]
