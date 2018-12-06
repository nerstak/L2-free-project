'use strict';

angular.module('app')
    .config(['$locationProvider', '$urlRouterProvider', function AppConfig($locationProvider, $urlRouterProvider) {
        $urlRouterProvider.otherwise('/');
        $locationProvider.html5Mode(true);
        $locationProvider.hashPrefix('!');
    }]);
