angular.module('app.services', [])
.constant('URL_API', 'http://desputados.devmsistemas.com.br/')

.factory('BlankFactory', [function(){

}])

.service('QuestoesService', function($http, $q, URL_API){
	this.buscaQuestoes = function(idCategoria) {
		var deferred = $q.defer();

		$http.get(URL_API + 'api/questoes/' + idCategoria)
		.success(function (data) {
			deferred.resolve(data);
		})
		.error(function(data) {
			deferred.reject(data);
		});

		return deferred.promise;
	};
})

.service('ScoreService', function($http, $q, $httpParamSerializer, URL_API){
	this.addScore = function(idUser){
		$http.post(URL_API +'api/ranking/',$httpParamSerializer({ idUsuario: idUser }));
	}

	this.buscaRanking = function(){
		var deferred = $q.defer();

		$http.get(URL_API + 'api/ranking/')
		.success(function (data) {
			deferred.resolve(data);
		})
		.error(function(data) {
			deferred.reject(data);
		});
		return deferred.promise;
	}

	this.buscaScore = function(idUser) {
		var deferred = $q.defer();

		$http.get(URL_API + 'api/ranking/' + idUser)
		.success(function (data) {
			deferred.resolve(data);
		})
		.error(function(data) {
			deferred.reject(data);
		});
		return deferred.promise;
	};
})

.service('LoginService', function($http, $q, $httpParamSerializer, URL_API){
	var logged;
	setUser = function(user){
		console.log("set User");
		logged = user;
		console.log(logged);
		if (!logged.sucesso){
			logged = null;
		}
	}

	this.getUser = function(){
		return logged;
	}

	this.validaUser = function(email){
		var deferred = $q.defer();

		$http.get(URL_API +'/api/usuario?email=' + email)
		.success(function (data) {
			deferred.resolve(data);
			setUser(data);
		})
		.error(function(data) {
			deferred.reject(data);
		});
		return deferred.promise;
	};

	this.cadastraUser = function(nome, email){
		console.log("service");
		console.log(nome);
		console.log(email);

		$http.post(URL_API +'api/usuario',$httpParamSerializer({ nome: nome, email: email }));
	};

});
