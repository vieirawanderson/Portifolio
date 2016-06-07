angular.module('app.routes', [])

.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider



      .state('login', {
    url: '/login',
    templateUrl: 'templates/login.html',
    controller: 'loginCtrl'
  })

  .state('menu', {
    url: '/menu',
    templateUrl: 'templates/menu.html',
    controller: 'menuCtrl'
  })

  .state('pergunta_Random', {
    url: '/rand/:categoria',
    templateUrl: 'templates/pergunta_Rand.html',
    controller: 'mainController'
  })

  // .state('pergunta_Bio', {
  //   url: '/bio',
  //   templateUrl: 'templates/pergunta_Bio.html',
  //   controller: 'pergunta_BioCtrl'
  // })
  //
  // .state('pergunta_Quim', {
  //   url: '/quimica',
  //   templateUrl: 'templates/pergunta_Quim.html',
  //   controller: 'pergunta_QuimCtrl'
  // })
  //
  // .state('pergunta_Fis', {
  //   url: '/fisica',
  //   templateUrl: 'templates/pergunta_Fis.html',
  //   controller: 'pergunta_FisCtrl'
  // })
  //
  // .state('pergunta_Port', {
  //   url: '/port',
  //   templateUrl: 'templates/pergunta_Port.html',
  //   controller: 'pergunta_PortCtrl'
  // })
  //
  // .state('pergunta_His', {
  //   url: '/historia',
  //   templateUrl: 'templates/pergunta_His.html',
  //   controller: 'pergunta_HisCtrl'
  // })
  //
  // .state('pergunta_Geo', {
  //   url: '/geografia',
  //   templateUrl: 'templates/pergunta_Geo.html',
  //   controller: 'pergunta_GeoCtrl'
  // })
  //
  // .state('pergunta_Ingles', {
  //   url: '/ingles',
  //   templateUrl: 'templates/pergunta_Ingles.html',
  //   controller: 'pergunta_InglesCtrl'
  // })
  //
  // .state('pergunta_Atual', {
  //   url: '/atual',
  //   templateUrl: 'templates/pergunta_Atual.html',
  //   controller: 'pergunta_AtualCtrl'
  // })
  //
  // .state('pergunta_FilSol', {
  //   url: '/filosofia',
  //   templateUrl: 'templates/pergunta_FilSol.html',
  //   controller: 'pergunta_FilSolCtrl'
  // })

  .state('rank', {
    url: '/ranking',
    templateUrl: 'templates/rank.html',
    controller: 'rankCtrl'
  })

  .state('resultado', {
    url: '/result',
    templateUrl: 'templates/resultado.html',
    controller: 'resultadoCtrl'
  })

$urlRouterProvider.otherwise('/login')



});
