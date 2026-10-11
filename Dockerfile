# =========================================================================
# STAGE 1: Ijaarsa Koodii (Build Environment)
# =========================================================================
FROM alpine:3.19 AS builder

# Install C++ build tools, CMake, Git, and Asio headers
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    asio-dev

WORKDIR /app

# Copy source repository into container
COPY . .

# Build binary in Release mode with maximum parallelism
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# =========================================================================
# STAGE 2: Sirna Hojii Dhumaa (Minimal Production Runtime)
# =========================================================================
FROM alpine:3.19

# Security: Create dedicated non-root user and group
RUN addgroup -S appgroup && adduser -S appuser -G appgroup

# Install minimal runtime libraries required by Crow/Asio
RUN apk add --no-cache libstdc++ libgcc asio

WORKDIR /home/appuser

# Copy built binary from Stage 1 with explicit appuser permissions
COPY --from=builder --chown=appuser:appgroup /app/build/exponential_engine_api .

# Switch to non-root execution context
USER appuser

EXPOSE 18080

ENTRYPOINT ["./exponential_engine_api"]
