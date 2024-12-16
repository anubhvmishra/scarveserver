# Use an official Python runtime as a parent image
FROM python:3.8-slim-buster

# Set the working directory in the container
WORKDIR /app

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential libopencv-dev

# Copy the current directory contents into the container at /app
COPY . /app

# Install any needed packages specified in requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Compile the C++ executable
RUN g++ -o seamcarving seamcarving.cpp `pkg-config --cflags --libs opencv4`

# Run the application
CMD ["gunicorn", "api:app"]