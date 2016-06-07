using Desputados.API.Repositorio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Desputados.API.Models
{
    public class Ranking
    {
        public string nomeUsuario { get; set; }

        public int pontuacao { get; set; }

        public static implicit operator Ranking(ranking_usuario ru)
        {
            if (ru == null)
                return null;

            var r = new Ranking();

            if (ru.usuarios != null)
                r.nomeUsuario = ru.usuarios.NOME;

            r.pontuacao = ru.PONTUACAO;

            return r;
        }
    }

    public class RankingRequest
    {
        public int idUsuario { get; set; }
    }
}
