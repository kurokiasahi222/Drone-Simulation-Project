# Workshop 5 Command Cheatsheet

## Dockerfile Instructions

`RUN <linux style command>`
- Allows you to run any command relevant to the docker image your creating
- Since our image is based on the ubuntu parent image, the commands we use with `RUN` will all be normal linux commands
- Also worth noting, the commands specified by `RUN` only pertain to the image, and will not affect your local computer in any way.

`COPY <src> <dest>`
- Copies files on local computer (`<src>`) to a specified location in our docker image (`<dest>`)
- This is the instruction we use when we want to move our entire project file tree onto our image

`WORKDIR <path>`
- Changes the directory inside the docker image 
- This is analogous to the `cd` command in linux

`CMD [ "list", "of", "args" ]`
- This instruction is actually never called in the build process of our image
- Instead, when we create a container derived from our image, the command specified by `CMD` is what's actually run by our container
- **HINT**: the command specified by `CMD` should run indefinitely, as containers only run as long as their default command persists

## Build Command
```bash
docker build -t <image name> <path to files>
```ls

This command should be run in the same folder as your `Dockerfile`.  It uses the instructions outlined in your `Dockerfile` to build your image.

- `-t` flag: allows you to specify an image name instead of what docker defaults to

- `<image name>`: The naming convention for this image MUST start with your docker username followed by '/', this is the only way (that i'm aware of) Docker will allow you to push your image up to Docker Hub for the workshop 5 submission.80

- `<path to files>`: The relative file path that will be used in our Dockerfile.  Since our Dockerfile is in the root of our project, and we just want to copy this whole project onto our docker image, we will always use `.` for this argument

## Run Command
```bash
docker run --rm -it -p <local port>:<container port> <image name>
```
- `--rm`: this says that once the container is finished running, automatically delete it.  Not adding this flag will leave dangling Docker containers which you most likely won't ever use again anyway.
  <!-- - If you want to delete all your unused containers, you can run `docker ps -aq | xargs docker rm` -->

- `-it`: tells Docker that it should make the container instance interactive, which should allow you to `^C` out of it, but it doesn't always work

- `-p <local_port>:<docker_port>`: allows you to forward ports from your docker container to your local computer.  First number is the port you want to use on your local computer, and the second port is the port your docker container is running on

## Push Command
```bash
docker push <image name>
```
This is the command you will use to actually send your image up to Docker Hub.  Before running this, make sure:
1. You're logged in to your Docker Hub account (`docker login` is the command you should have run)
2. Your image name starts with your Docker Hub username followed by a '/' and whatever you want to name it after the '/'

## Other Useful Commands
- `^P^Q`: The `^` stands for the "Ctrl" key.  If your docker container is running in the foreground and you can't type `^C` to quit it, you can instead use this to detach your docker container
  - **NOTE**: Although your container is detached, that doesn't mean it's not running, you'll need to separately kill the container with this next command

- `docker kill <container name>`: For any running docker container specified by `<container name>`, this command will terminate it
  - If you have multiple running docker containers and want to terminate them all at once, or you simply couldn't be bothered to type the name of your container, you can run `docker ps -q | xargs docker kill`

- `docker rm <container name>`: Killing your docker container doesn't necessarily mean you can't access it, so if you're like me, and you want to clean up after yourself, this command will fully remove any dangling docker containers
  - again, if you want to remove all unused docker containers, run `docker ps -aq | xargs docker rm`

- `docker rmi <image name>`: This command is for when you no longer have a use for your docker image, and you want to free up some space.  You probably won't need to use this, but it's helpful to keep in mind
  - `docker image ls -q | xargs docker rmi` removes all images

## Docker Compose
As shown, Docker can be a very powerful tool once you get past the initial learning curve, but memorizing all these flags to run our container can be quite the hassle.  For this reason, i've provided a `docker-compose.yml` file to help ease this process.

Before going any further, open `docker-compose.yml` and switch out `<docker_username>` with your docker username.

This `docker-compose` file abstracts the process of running the docker image, so instead of running that long command above, you can instead run:
```bash
docker compose up -d
```
This will start your container, forward the ports, and it will even mount the `libs/transit` directory and the `app` directory onto the container, meaning any changes you make to these directories while the container is running will change the files in the container real-time.

This doesn't really make much of a difference though, as the code is already compiled based off your code from before calling `docker build`, but it may be useful for other projects!

Once your done with this container instance, you can simply run:
```bash
docker compose down
```

Note that `docker compose` is really only used for the development of your image, and if other people are pulling your image from Docker Hub, they won't have access to your `docker-compose.yml`, so you should specify how to run your image without it on Docker Hub.

