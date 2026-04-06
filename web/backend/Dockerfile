# Build stage
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app/src

# Clone Crow framework
RUN git clone --depth 1 --branch v1.1 https://github.com/CrowCpp/Crow.git

# Copy source (include/nlohmann/json.hpp already in repo)
COPY . /app/src/

# Build
WORKDIR /app/build
RUN cmake -DCMAKE_BUILD_TYPE=Release .. && make -j$(nproc)

# Runtime stage
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
