; ModuleID = 'ac'
source_filename = "ac"

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #0

declare void @__builtin_va_start(i8*)

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #0

declare void @__builtin_va_end(i8*)

; Function Attrs: nounwind willreturn
declare void @llvm.assume(i1) #1

; Function Attrs: nounwind
declare i64 @llvm.readcyclecounter() #0

; Function Attrs: nounwind readnone speculatable willreturn
declare i8 @llvm.bitreverse.i8(i8) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i16 @llvm.bitreverse.i16(i16) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i32 @llvm.bitreverse.i32(i32) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.bitreverse.i64(i64) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i8 @llvm.fshl.i8(i8, i8) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i16 @llvm.fshl.i16(i16, i16) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i32 @llvm.fshl.i32(i32, i32) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.fshl.i64(i64, i64) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i8 @llvm.fshr.i8(i8, i8) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i16 @llvm.fshr.i16(i16, i16) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i32 @llvm.fshr.i32(i32, i32) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.fshr.i64(i64, i64) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare double @llvm.canonicalize.f64(double) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare float @llvm.canonicalize.f32(float) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare fp128 @llvm.canonicalize.f80(fp128) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1 immarg, i1 immarg, i1 immarg) #2

attributes #0 = { nounwind }
attributes #1 = { nounwind willreturn }
attributes #2 = { nounwind readnone speculatable willreturn }
