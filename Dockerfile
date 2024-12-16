# Use an official Ubuntu as a parent image
FROM ubuntu:20.04

# Set the working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libopencv-dev

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the OpenCV project
RUN g++ -o seamcarving seamcarving.cpp `pkg-config --cflags --libs opencv4`

# Run the executable
CMD ["./seamcarving"]