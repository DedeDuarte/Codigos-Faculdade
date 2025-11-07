import sys

def solve_eq(eq:str, vars:dict[str, float]) -> float:
    """
    Resolve a equação matemática de 'eq'

    Args:
        eq(str): Equação a ser resolvida
        vars(dict): Dicionario com as variaveis

    Returns:
        float: Valor do resultado
    """
    return eval(eq, {'__builtins__': None}, vars)

def find_p(a:float, b:float) -> float:
    """
    Encontra o P, ou seja, o meio termo entre 'a' e 'b'

    Args:
        a(float): Valor de 'a'
        b(float): Valor de 'b'

    Returns:
        float: Valor do resultado
    """
    x = abs(a-b) / 2
    return a + x if a < b else b + x

def debug(i:int, a:float, a_val:float, b:float, b_val:float, p:float, p_val:float, invert:float) -> None:
    """
    Função usada para printar todas as informações de cada iteração

    Args:
        i(int): Quantidade de iterações
        a(float): Valor de 'a'
        a_val(float): Valor de 'f(a)'
        b(float): Valor de 'b'
        b_val(float): Valor de 'f(b)'
        p(float): Valor de 'p'
        p_val(float): Valor de 'f(p)'
        invert(float): valor da multiplicação entre 'a_val' e 'b_'val. Usado para saber qual deve ser substituido por 'p'

    Returns:
        None: Sem retorno
    """
    print(f'Iteração  {i}:')
    print(f'     a: {a} ({a_val})')
    print(f'     b: {b} ({b_val})')
    print(f'     p: {p} ({p_val})\n')

    print(f'     {invert}')
    print(f'     {invert < 0}\n')


def bisseccao(eq:str, a:float, b:float, er:float) -> float:
    """
    Calcula por 'bissecção' o valor aproximado da raiz de 'f(x)' entre 'a' e 'b'

    Args:
        eq(str): Equação de f(x)
        a(float): Posição inicial de X
        b(float): Posição final de X
        er(float): Erro aceito

    Returns:
        Float: Resposta aproximada

    Nota:
        Use '-d' ao chamar o programa para executar no modo debug
    """
    a_val = solve_eq(eq, {'x': a})
    b_val = solve_eq(eq, {'x': b})
    p_val = float('inf')    # Inicialização
    p = float(0)            # Inicialização

    if a_val * b_val > 0:
        print(f'O intervalo [{a}, {b}] não contém raiz (f(a) e f(b) têm o mesmo sinal ou a função f(x) está errada).')
        exit()

    i = 1
    while abs(p_val) >= er:
        p = find_p(a, b)
        a_val = solve_eq(eq, {'x': a})
        b_val = solve_eq(eq, {'x': b})
        p_val = solve_eq(eq, {'x': p})

        invert = a_val*p_val
        if invert < 0: b = p
        else: a = p

        i += 1
        if ('-d' in sys.argv): debug(i, a, a_val, b, b_val, p, p_val, invert)

    return p
        

def input_float(msg:str) -> float:
    """
    Verifica se o usuário realmente deu input de 'float'

    Args:
        msg(str): Mensagem do input

    Returns:
        float: Input do usuário
    """
    while True:
        try:
            return float(input(msg))
        except ValueError:
            print(f'\nValor deve ser um float! Tente de novo!')

if __name__ == '__main__':
    # Função principal de input do usuário
    #
    # Nota:
    #     Use '-d' ao chamar o programa para executar no modo debug
    res = float('inf')

    while res == float('inf'):
        eq =       input('f(x) = ').strip().replace(' ', '').lower()
        a  = input_float('  a  = ')
        b  = input_float('  b  = ')
        er = input_float('  er = ')

        print(f'\nf(x) = {eq}\nIntervalo: [{a}, {b}]\nErro: {er}')

        try:
            res = bisseccao(eq, a, b, er)
        except Exception as e:
            print(f'\nErro ao calcular o resultado: {e}')
            print( 'Nao use contracoes como "4x", use "4*x"')
            print( "So sao aceitos números, X, +, -, *, /, **, e '.' em f(x)")
            print( 'Verifique os inputs e tente novamente!\n')

    print(f'Resultado: {res}')
