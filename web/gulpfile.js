/* eslint-disable */

/**
 * Modules dependencies
 */

var gulp = require('gulp');

var connect = require('gulp-connect');
var eslint = require('gulp-eslint');
var uglify = require('gulp-uglify');
var less = require('gulp-less');
var plumber = require('gulp-plumber');
var cleanCSS = require('gulp-clean-css');
var del = require('del');
var usemin = require('gulp-usemin');
var rev = require('gulp-rev');
var runSequence = require('run-sequence');
var imagemin = require('gulp-imagemin');

/**
 * Tasks
 */

gulp.task('less', function lessFn() {
    return gulp
        .src('./src/assets/less/app.less')
        .pipe(plumber())
        .pipe(less())
        .pipe(cleanCSS())
        .pipe(gulp.dest('./src/assets/css/'));
});

gulp.task('lint', function lint() {
    return gulp
        .src([
            './src/**/*.js',
            '!./src/libs/**',
            '!./src/assets/libs/**',
            '!./src/assets/js/**',
            '!./src/directives/inspinia.js',
            '!./dist/**',
        ])
        .pipe(eslint())
        .pipe(eslint.formatEach('compact', process.stderr));
});

gulp.task('lintProd', function lintProd() {
    return gulp
        .src([
            './src/**/*.js',
            '!./src/libs/**',
            '!./src/assets/libs/**',
            '!./src/assets/js/**',
            '!./src/directives/inspinia.js',
            '!./dist/**',
        ])
        .pipe(eslint())
        .pipe(eslint.formatEach('compact', process.stderr))
        .pipe(eslint.failAfterError());
});

gulp.task('clean', function clean() {
    return del([
        './dist/'
    ]);
});

gulp.task('usemin',function() {
    return gulp
        .src('./src/index.html')
        .pipe(usemin({
            cssLib: [cleanCSS, rev],
            cssMain: [cleanCSS, rev],
            jsLib: [uglify, rev],
            jsMain: [uglify, rev],
        }))
        .pipe(gulp.dest('./dist/'));
});

gulp.task('optimize-images', function optimizeImages() {
    return gulp
        .src('./src/assets/img/**')
        .pipe(imagemin())
        .pipe(gulp.dest('./dist/assets/img'));
});

gulp.task('copy-html-files', function copyHtmlFiles() {
    return gulp
        .src([
            './src/**/*.html',
            '!./src/index.html',
            '!./src/{libs,libs/**}',
            '!./src/assets/{libs,libs/**}',
        ])
        .pipe(gulp.dest('./dist/'));
});

gulp.task('copy-assets-files', function copyAssetsFiles() {
    return gulp
        .src([
            './src/assets/**/*',
            '!./src/assets/{css,css/**}',
            '!./src/assets/{less,less/**}',
            '!./src/assets/{img,img/**}',
            '!./src/assets/{libs,libs/**}',
        ])
        .pipe(gulp.dest('./dist/assets'));
});

gulp.task('copy-fonts-files', function copyFontsFiles() {
    return gulp
        .src([
            './src/libs/material-design-icons/iconfont/*.{eot,woff2,woff,ttf}',
        ])
        .pipe(gulp.dest('./dist/assets/css'));
});

/**
 * Watchers
 */

gulp.task('watch', function watch(done) {
    return gulp.parallel('watch:less', 'watch:js')(done);
});

gulp.task('watch:less', function watchLess(done) {
    gulp
        .watch([
            './src/assets/less/**'
        ], gulp.series('less'));

    return done();
});

gulp.task('watch:js', function watchJs(done) {
    gulp
        .watch([
            './src/**/*.js',
            '!./src/libs/**',
            '!./src/assets/**'
        ], gulp.series('lint'));

    return done();
});

/**
 * Servers
 */

gulp.task('connect', function connectFn(done) {
    connect.server({
        root: 'src/',
        host: '0.0.0.0',
        port: 8888,
        fallback: 'src/index.html',
    });

    return done();
});

gulp.task('connectDist', function connectDist(done) {
    connect.server({
        root: 'dist/',
        host: '0.0.0.0',
        port: 9999,
        fallback: 'dist/index.html',
    });

    return done();
});

/**
 * Processes
 */

gulp.task('build', gulp.series(
    'less',
    'lintProd',
    'clean',
    'usemin',
    'copy-html-files',
    'copy-assets-files',
    'copy-fonts-files',
    'optimize-images'
));

gulp.task('dist', gulp.series(
    'build',
    'connectDist'
));

gulp.task('default', function defaultTask(done) {
    gulp.series(
        'lint',
        'less'
    )(() => {
        return gulp.parallel(
            'connect',
            'watch'
        )(done);
    });
});

/* eslint-enable */
