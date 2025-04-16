# CustomDataTypesMathsForGames

This repository contains a collection of custom C++ data types for 3D mathematics, created to be compatible with a unit test framework provided by the Academy of Interactive Entertainment (AIE). To test this project, in Visual Studio go to Test > Test Explorer > Run All Tests.

All math types are implemented in **column-major order** using a **right-handed coordinate system**, and reside in the `MathClasses` namespace.

## Data Types Implemented

### Vector3
A 3D vector with:
- Public fields: `x`, `y`, `z`
- Supports operations: addition, subtraction, scalar multiplication, dot product, cross product
- Methods: `Magnitude()`, `Normalise()`, `Normalised()`, `ToString()`
- Subscript operator `[]` and cast to `float*`

### Vector4
A 4D homogeneous vector with:
- Public fields: `x`, `y`, `z`, `w`
- Same functionality as `Vector3`, adapted for 4D
- Cross product includes `w = 0`
- Fully compatible with matrix transformations

### Matrix3
A 3x3 matrix for 2D transformations and rotations:
- Public fields: `m1` through `m9`
- Methods: `setRotateX/Y/Z()`, `setTranslate()`, `Transposed()`
- Operators: multiplication with `Matrix3` and `Vector3`, scalar ops
- Static builders: `MakeIdentity()`, `MakeTranslation()`, `MakeEuler()`, `MakeScale()`

### Matrix4
A 4x4 matrix for 3D transformations:
- Public fields: `m1` through `m16`
- Contains axes: `xAxis`, `yAxis`, `zAxis`, `translation`
- Methods: `SetRotateX/Y/Z()`, `MakeEuler()`, `MakeScale()`, `Magnitude()`, `Normalize()`
- Multiplication with `Matrix4` and `Vector4`
- Cast to `float*` and access via `[]`

### Colour
Stores RGBA values packed into a 4-byte `unsigned int`:
- Methods: `GetRed/Green/Blue/Alpha()`, `SetRed/Green/Blue/Alpha()`
- Uses bitwise operations for manipulation
- Constructor from 4 `unsigned char` values
