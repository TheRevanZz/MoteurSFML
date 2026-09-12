param(
    [ValidateSet("Debug","Release")]
    [string]$BuildType = "Debug"
)

cmake --build build --config $BuildType