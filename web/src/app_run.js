'use strict';

angular.module('app')

    .run(['$rootScope', '$state', function AppRun($rootScope, $state) {
        $rootScope.currentState = $state;
        $rootScope.previousState = null;

        if (navigator.userAgent.toLowerCase().match(/chrome/)) {
            angular.element(document).find('body').toggleClass('dab-enabled');
        }

        $rootScope.$on('$stateChangeSuccess', function stateChangeSuccessFn(event, toState, toParams, from) {
            $rootScope.previousState = from;
            $rootScope.currentState = toState;

            var title = toState.title;

            if (toState.noTitle) {
                $rootScope.pageTitle = toState.title;

                return true;
            }

            title = title ? ' \u2014 ' + title : '';

            $rootScope.pageTitle = __env.brandName + title;

            if (!$rootScope.currentState.title) {
                $rootScope.currentState.title = __env.brandName;
            }

            return true;
        });
    }]);
