# Build stage
FROM alpine:3.19 AS builder

RUN apk add --no-cache \
    cmake \
    g++ \
    make \
    git

WORKDIR /app

# Clone Crow framework
RUN git clone --depth 1 --branch v1.1 https://github.com/CrowCpp/Crow.git

# Copy source
COPY . /app/src/

# Build
RUN mkdir /app/build && \
    cd /app/build && \
    cmake -DCMAKE_BUILD_TYPE=Release /app/src && \
    make -j$(nproc)

# Runtime stage
FROM alpine:3.19

RUN apk add --no-cache libgcc libstdc++

WORKDIR /app
COPY --from=builder /app/build/backend /app/backend

ENV PORT=10000
EXPOSE 10000

CMD ["./backend"]
