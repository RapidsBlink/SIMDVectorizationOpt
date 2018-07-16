import os

if __name__ == '__main__':
    exec_name_lst = ['avx2_chromium_disable_deserialize', 'avx2_chromium_enable_deserialize',
                     'chromium_disable_deserialize', 'chromium_enable_deserialize',
                     'naive_comp_disable_deserialize', 'naive_comp_enable_deserialize',
                     'naive_lookup_disable_deserialize', 'naive_lookup_enable_deserialize']

    base_path = os.curdir
    print 'cur dir:', base_path
    stat_dir = os.sep.join([base_path, 'stat-50-200'])
    os.system('mkdir -p ' + stat_dir)
    for exec_name in exec_name_lst:
        cmd = ' '.join([os.sep.join([base_path, '..', 'cmake-build-debug', 'src', 'playground', exec_name]), '>',
                        os.sep.join([stat_dir, exec_name + '.txt'])])
        print cmd
        os.system(cmd)
