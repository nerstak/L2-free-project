'use strict';

angular.module('app.core', ['ui.router'])

    .config(['$stateProvider', function CoreConfig($stateProvider) {
        $stateProvider
            .state('index', {
                controller: 'IndexController',
                controllerAs: 'vm',
                templateUrl: 'modules/core/views/core_index_page.html',
                url: '/',
                title: '',
            });
    }])

    .controller('IndexController', [function IndexController() {
        var self = this;
    }]);
