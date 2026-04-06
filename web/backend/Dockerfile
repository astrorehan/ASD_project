# Stage 1: Build
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    git \
    curl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Clone Crow framework
RUN git clone --depth 1 --branch v1.1 https://github.com/CrowCpp/Crow.git

# Download nlohmann/json
RUN mkdir -p /app/src/vendor && \
    curl -L https://raw.githubusercontent.com/nlohmann/json/v3.11.3/single_include/nlohmann/json.hpp \
    -o /app/src/vendor/json.hpp

# Copy source (exclude vendor - we download it above)
COPY . /app/src/

# Build
RUN mkdir /app/build && \
    cd /app/build && \
    cmake -DCMAKE_BUILD_TYPE=Release /app/src && \
    make -j$(nproc)

# Stage 2: Runtime
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libstdc++6 \
    libgcc-s1 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/backend /app/backend

ENV PORT=10000
EXPOSE 10000

CMD ["./backend"]
