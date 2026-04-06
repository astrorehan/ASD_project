# Build stage
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    cmake g++ make git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Clone Crow framework
RUN git clone --depth 1 --branch v1.1 https://github.com/CrowCpp/Crow.git

# Copy repo to /app (context is repo root)
COPY . /app/

# Build only backend
WORKDIR /app/build
RUN cmake -DCMAKE_BUILD_TYPE=Release /app/web/backend && make -j$(nproc)

# Runtime stage
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libstdc++6 libgcc-s1 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/backend /app/backend

ENV PORT=10000
EXPOSE 10000
CMD ["./backend"]
