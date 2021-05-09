; ModuleID = 'a.c'
source_filename = "a.c"

define i32 @fun(i32 %a, i32 %b) !dbg !5 {
entry:
  %add = add i32 %a, %b
  ret i32 %add
}

define i32 @main() !dbg !9 {
entry:
  %fun_result = call i32 @fun(i32 1, i32 2), !dbg !11
  %a = alloca i32, align 4, !dbg !12
  store i32 0, i32* %a, align 4, !dbg !12
  %b = alloca i32, align 4, !dbg !13
  store i32 1, i32* %b, align 4, !dbg !13
  %b1 = load i32, i32* %b, align 4, !dbg !14
  %a2 = load i32, i32* %a, align 4, !dbg !14
  %div = sdiv i32 %b1, %a2, !dbg !14
  %c = alloca i32, align 4, !dbg !14
  store i32 %div, i32* %c, align 4, !dbg !14
  ret i32 0, !dbg !15
}

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "come", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false)
!1 = !DIFile(filename: "a.c", directory: "/home/ab25cq/repo/comelang")
!2 = !{}
!3 = !{i32 5, !"Dwarf Versio", i32 4}
!4 = !{i32 5, !"Debug Info Version", i32 3}
!5 = distinct !DISubprogram(name: "fun", linkageName: "fun", scope: !1, file: !1, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!6 = !DISubroutineType(types: !7)
!7 = !{!8, !8}
!8 = !DIBasicType(name: "int", size: 32)
!9 = distinct !DISubprogram(name: "main", linkageName: "main", scope: !1, file: !1, line: 6, type: !10, scopeLine: 6, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DISubroutineType(types: !2)
!11 = !DILocation(line: 3, scope: !5)
!12 = !DILocation(line: 8, scope: !9)
!13 = !DILocation(line: 10, scope: !9)
!14 = !DILocation(line: 11, scope: !9)
!15 = !DILocation(line: 12, scope: !9)
