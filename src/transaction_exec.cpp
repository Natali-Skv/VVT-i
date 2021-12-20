#include "transaction_exec.h"


void TransactionExec::simple_transaction_exec(std::string sql_request, pqxx::connection *connection) {
    pqxx::work transaction(*connection);
    
    try {
        transaction.exec(sql_request);
        transaction.commit();
    } catch (const pqxx::sql_error &e) {
        transaction.abort();
        std::cout << e.what() << "\n";
        throw(e.what());
    }
}


bool TransactionExec::trans_check_empty_exec(std::string sql_request, pqxx::connection *connection) {
    pqxx::work transaction(*connection);
    
    try {
        pqxx::result res = transaction.exec(sql_request);
        transaction.commit();

        if (res.empty()) {
            return true;
        }
        
        return false;
    } catch (const pqxx::sql_error &e) {
        transaction.abort();
        std::cout << e.what() << "\n";
        throw(e.what());
    }
}


int TransactionExec::trans_one_int_value_exec(std::string sql_request, pqxx::connection *connection) {
    pqxx::work transaction(*connection);
    
    try {
        pqxx::result res = transaction.exec(sql_request);
        transaction.commit();

        if (res.empty()) {
            return -1;
        }

        return res[0][0].as<int>();
    } catch (const pqxx::sql_error &e) {
        transaction.abort();
        std::cout << e.what() << "\n";
        throw(e.what());
    }
}


std::string TransactionExec::trans_one_string_value_exec(std::string sql_request, pqxx::connection *connection) {
    pqxx::work transaction(*connection);
    
    try {
        pqxx::result res = transaction.exec(sql_request);
        transaction.commit();

        if (res.empty()) {
            return "";
        }

        return res[0][0].as<std::string>();
    } catch (const pqxx::sql_error &e) {
        transaction.abort();
        std::cout << e.what() << "\n";
        throw(e.what());
    }
}


std::string TransactionExec::get_name_dir(std::string dir_path) {

    return dir_path.substr(dir_path.find_last_of('/') + 1, dir_path.length());
}


std::string TransactionExec::trans_ls_exec(std::string sql_request_file,
                        std::string sql_request_dir, pqxx::connection *connection) {
    
    pqxx::work transaction(*connection);
    std::string ls_result = "";
    
    try {
        pqxx::result res = transaction.exec(sql_request_file);

        std::cout << res.size() << std::endl;

        for (int i = 0; i < res.size(); ++i) {
            ls_result += fmt::format("-{0}  {1}  {2}\n", BASE_ACCESS_LVL, 
                    res[i][0].as<std::string>(), res[i][1].as<std::string>());
            // ls_result += "-" + base_access_lvl + "  " + res[i][0].as<std::string>() + "  " + res[i][1].as<std::string>() + "\n";
        }

        res = transaction.exec(sql_request_dir);
        transaction.commit();

        for (int i = 0; i < res.size(); ++i) {
            ls_result += fmt::format("d{0}  {1}  {2}\n", BASE_ACCESS_LVL, 
                    res[i][0].as<std::string>(), res[i][1].as<std::string>());
            // ls_result += "d" + base_access_lvl + "  " + get_name_dir(res[i][0].as<std::string>()) + "  " + res[i][1].as<std::string>() + "\n";
        }

        return ls_result;

    } catch (const pqxx::sql_error &e) {
        transaction.abort();
        std::cout << e.what() << "\n";
        throw(e.what());
    }
}
