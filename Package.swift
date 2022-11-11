// swift-tools-version:5.5
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "KindKit2",
    platforms: [
        .iOS(.v10),
        .macOS(.v10_14)
    ],
    products: [
        .library(name: "KindKit2", type: .static, targets: [ "KindKit2" ])
    ],
    targets: [
        .target(
            name: "libkk2",
            path: "Library",
            exclude: [ "test" ],
            sources: [ "src" ],
            publicHeadersPath: "inc"
        ),
        .target(
            name: "KindKit2",
            dependencies: [ .target(name: "libkk2") ],
            path: "Swift/Library"
        ),
        .testTarget(
            name: "KindKit2-Tests",
            dependencies: [ .target(name: "KindKit2") ],
            path: "Swift/Tests"
        )
    ],
    cLanguageStandard: .c2x
)
