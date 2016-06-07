using Desputados.API.Repositorio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Desputados.API.Models
{
    public class Questao
    {
        public int id { get; set; }

        public Categoria categoria { get; set; }

        public string enunciado { get; set; }

        public string resolucao { get; set; }

        public List<Alternativa> alternativas { get; set; }

        public static implicit operator Questao(questoes questao)
        {
            if (questao == null)
                return null;

            var q = new Questao();

            q.id = questao.ID;
            q.enunciado = questao.ENUNCIADO;
            q.resolucao = questao.RESOLUCAO;

            if(questao.alternativas != null)
            {
                q.alternativas = new List<Alternativa>(questao.alternativas.Count);

                foreach (var item in questao.alternativas)
                    q.alternativas.Add(item);
            }

            return q;
        }
    }
}
