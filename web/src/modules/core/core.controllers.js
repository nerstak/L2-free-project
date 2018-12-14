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

    .controller('IndexController', ['$uibModal', function IndexController($uibModal) {
        var self = this;

        var video = angular.element(document).find('video')[0];

        video.onended = function onEnded() {
            video.play();
        };

        self.downloadMe = function downloadMe() {
            var modalInstance = $uibModal.open({
                controller: 'Download_Core_ModalController',
                controllerAs: 'vm',
                templateUrl: 'modules/core/views/modals/core_download_modal.html',
            });

            modalInstance.result.then(function result() {
                console.log('Yo');
            }).catch(function error() { modalInstance.close(); });
        };
    }])

    // eslint-disable-next-line camelcase
    .controller('Download_Core_ModalController', ['$uibModalInstance', function Download_Core_ModalController($uibModalInstance) {
        var self = this;

        self.ok = function ok() {
            $uibModalInstance.close();
        };

        self.cancel = function cancel() {
            $uibModalInstance.dismiss('cancel');
        };
    }]);
