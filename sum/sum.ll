; ModuleID = 'sum.c'
source_filename = "sum.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [19 x i8] c"\C7\EB\CA\E4\C8\EB\D2\BB\B8\F6\D5\FD\D5\FB\CA\FD\A3\BA\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.2 = private unnamed_addr constant [20 x i8] c"\C7\EB\CA\E4\C8\EB\D2\BB\B8\F6\D5\FD\D5\FB\CA\FD\A1\A3\0A\00", align 1
@.str.3 = private unnamed_addr constant [28 x i8] c"\B4\D31\B5\BD%d\B5\C4\D5\FB\CA\FD\B5\C4\C0\DB\BC\D3\BA\CD\CA\C7 %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @sum(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  %4 = load i32, i32* %3, align 4
  %5 = icmp eq i32 %4, 1
  br i1 %5, label %6, label %7

6:                                                ; preds = %1
  store i32 1, i32* %2, align 4
  br label %13

7:                                                ; preds = %1
  %8 = load i32, i32* %3, align 4
  %9 = load i32, i32* %3, align 4
  %10 = sub nsw i32 %9, 1
  %11 = call i32 @sum(i32 noundef %10)
  %12 = add nsw i32 %8, %11
  store i32 %12, i32* %2, align 4
  br label %13

13:                                               ; preds = %7, %6
  %14 = load i32, i32* %2, align 4
  ret i32 %14
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %3 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i64 0, i64 0))
  %4 = call i32 (i8*, i32*, ...) bitcast (i32 (...)* @scanf_s to i32 (i8*, i32*, ...)*)(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i64 0, i64 0), i32* noundef %2)
  %5 = load i32, i32* %2, align 4
  %6 = icmp slt i32 %5, 1
  br i1 %6, label %7, label %9

7:                                                ; preds = %0
  %8 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([20 x i8], [20 x i8]* @.str.2, i64 0, i64 0))
  store i32 1, i32* %1, align 4
  br label %14

9:                                                ; preds = %0
  %10 = load i32, i32* %2, align 4
  %11 = load i32, i32* %2, align 4
  %12 = call i32 @sum(i32 noundef %11)
  %13 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([28 x i8], [28 x i8]* @.str.3, i64 0, i64 0), i32 noundef %10, i32 noundef %12)
  store i32 0, i32* %1, align 4
  br label %14

14:                                               ; preds = %9, %7
  %15 = load i32, i32* %1, align 4
  ret i32 %15
}

declare i32 @printf(i8* noundef, ...) #1

declare i32 @scanf_s(...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
