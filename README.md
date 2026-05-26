# muni-web-server-c

A collection of educational web server implementations created for lectures and experiments at Masaryk University (MUNI).

The repository contains multiple versions of a simple HTTP server implemented in different languages and architectural styles to demonstrate low-level networking, request handling, concurrency, logging, and observability concepts.

## Repository Structure

- `main` — Original C implementation of the web server
- `version_2` — Refactored/improved second version of the C server
- `go-version` — Go implementation of the same server concepts
- `golang-kibana` — Go server integrated with logging/monitoring tooling (Kibana/ELK stack)

## Goals

This project was created primarily for teaching purposes and experimentation with:

- TCP socket programming
- HTTP protocol basics
- Request parsing and response generation
- Static file serving
- Concurrency models
- Logging and observability
- Comparing C and Go server implementations
- Understanding low-level server internals

## Technologies

Depending on the branch/version, the project uses:

- C
- Go
- POSIX sockets
- Docker
- Kibana / ELK stack

## Running

Each branch may contain a different setup and implementation approach.

Typical workflow:

```bash
git clone https://github.com/nodari-dev/muni-web-server-c.git
cd muni-web-server-c
git checkout <branch-name>
```

Examples:

```bash
git checkout main
```

```bash
git checkout go-version
```

## Educational Purpose

The codebase is intentionally simple and focused on clarity rather than production readiness.

It is designed to help students understand how web servers work internally by building them from scratch.

## License

This project is intended for educational and learning purposes.
