from subprocess import run, Popen, PIPE
from sys import executable

num_test = 1
is_ok = True
for i in range(1, 11):
    str_data =  "tests/end-to-end/" + str(i) + ".dat"
    file_in = open(str_data, "r")
    str_ans = "tests/end-to-end/" + str(i) + ".ans"

    ans_ord = []
    ans_mnoj = 0
    num = 0
    for i in open(str_ans):
        if num == 0:
            ans_ord = list(map(int, i.strip().split()))
            num += 1
        else:
            ans_mnoj = float(i)
	
    result = run(["build/src/main_chain"], capture_output = True, encoding='cp866', stdin=file_in)
    print("Test: " + str(num_test).strip())

    res = list(map(float, result.stdout.split()))
    res_ord = list(map(int, res[0:-1]))
    res_mnoj = res[-1]

    fl = True

    fl &= (abs(res_mnoj - ans_mnoj) <= 0.00001)
    if len(res_ord) == len(ans_ord):
        for i in range(len(res_ord)):
            if res_ord[i] != ans_ord[i]:
                fl = False
    else:
        fl = False

    is_ok &= fl

    if fl:
        print("OK")
    else:
        print("ERROR\nExpect order:", ans_ord, "\nExpect multiplier: ", ans_mnoj, "\nGive order:", res_ord, "\nGive multiplier: ", res_mnoj)
    print("-------------------------------------------------")
    num_test += 1

if is_ok:
	print("TESTS PASSED")
else:
	print("TESTS FAILED")