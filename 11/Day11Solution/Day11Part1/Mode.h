#pragma once
//Instruction Modes
// 0 - postion mode - intProgram[parameter]
// 1 - immeditate mode - parameter
// 2 - relative mode - intProgram[parameter + relativeBase]
enum class Mode { position, immediate, relative };